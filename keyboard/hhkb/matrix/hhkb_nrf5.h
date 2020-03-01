#ifndef HHKB_NRF5_H
#define HHKB_NRF5_H

#include <stdint.h>
#include <stdbool.h>
//#include <util/delay.h>
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"


// Timer resolution check
//#if (1000000/TIMER_RAW_FREQ > 20)
//#   error "Timer resolution(>20us) is not enough for HHKB matrix scan tweak on V-USB."
//#endif


/**
 * @brief HHKB Matrix I/O
 *
 * row:     HC4051[A,B,C]  selects scan row0-7
 * row-ext: [En0,En1] row extention for JP
 * col:     LS145[A,B,C,D] selects scan col0-7 and enable(D)
 * key:     on: 0/off: 1
 * prev:    hysteresis control: assert(1) when previous key state is on
 */

/**
 * @brief Controller PCB
--------------
    M38K07M4    Renesas MCU with USB function
                http://documentation.renesas.com/eng/products/mpumcu/rej03b0192_38k0ds.pdf

    (HHKB_controller.jpg)

Keyswitch PCB
-------------
    HC4051      Analog Multiplexer: select a row line.
                http://www.ti.com/lit/ds/schs122j/schs122j.pdf
    LS145       BCD Decoder: select a column line.
                http://www.ti.com/lit/ds/symlink/sn74ls145.pdf
    BU9831      Non-volatile electronic potentiometer: for calibration?
                https://www.spezial.com/doc/rohm-a/bu9831.pdf
    TP1683/4    Capacitive Sensing controller: no datasheet available.

    (HHKB_keyswitch.jpg)

    Topre original chip?
    (HHKB_TP1684.jpg)


Connector Cable
---------------
Two PCBs are connected by 15 lines(13 in case of Pro2).
Vcc and GND use 3(2) lines each, other lines are for keyboard signaling.

    HHKB connector lines:
    JP   Pro2   Pro     Function    Description                               TMK pin usage
    --------------------------------------------------------------------------------------------
                 1      Vcc(5V)                                               5V
     1    1      2      Vcc(5V)                                               5V
     2    2      3      Vcc(5V)                                               5V
     3    3      4      TP1684      ~KEY: Low(0) when key is pressed          PD7 input(with pullup)
     4    4      5      TP1684      HYS: High(1) when key is pressed          PB7 output
     5    5      6      HC4051      A(bit0)\                                  PB0 output
     6    6      7      HC4051      B(bit1) > select row 0-7                  PB1 output
     7    7      8      HC4051      C(bit2)/                                  PB2 output
     8    8      9      LS145       A(bit0)\                                  PB3 output
     9    9     10      LS145       B(bit1) > select column 0-7               PB4 output
    10   10     11      LS145       C(bit2)/                                  PB5 output
    11   11     12      LS145       ~D(enable) Low(0) enables selected column PB6 output
    12   12     13      GND                                                   GND
    13   13     14      GND                                                   GND
                15      GND
    14                  HC4051(Z2)  ~Enable of Z2   row0-7                    PC6
    15                  HC4051(Z3)  ~Enable of Z3   row8-15                   PC7

    NOTE: Probably HYS changes threshold for upstroke and makes hysteresis in the result.
    NOTE: HYS should be given High(1) when previous KEY state is Low(0).
    NOTE: 1KOhm didn't work as pullup resistor on KEY. AVR internal pullup or 10KOhm resistor was OK.
    NOTE: JP has two HC4051(Z2,Z3) and line 5, 6 and 7 are connected to both of them.
 * 
 */

/**
 * @brief nRF5的GPIO函数
 * uint32_t pin_number      :引脚编号，bit0~31对应引脚P0.00~P0.31
 * nrf_gpio_cfg_default     (uint32_t pin_number):释放GPIO状态，恢复最低功耗。
 * 
 * nrf_gpio_cfg_output      (uint32_t pin_number):设置指定引脚为输出方向。
 * nrf_gpio_pin_set         (uint32_t pin_number):驱动指定的GPIO输出高电平
 * nrf_gpio_pin_clear       (uint32_t pin_number):驱动指定的GPIO输出低电平
 * nrf_gpio_pin_toggle      (uint32_t pin_number):翻转指定的GPIO输出状态
 * 
 * nrf_gpio_cfg_input       (uint32_t pin_number,
 *                           nrf_gpio_pin_pull_t pull_config):设置指定引脚为输入方向。
 * nrf_gpio_cfg_sense_input (uint32_t pin_number,
 *                           nrf_gpio_pin_pull_t pull_config,
 *                           nrf_gpio_pin_sense_t sense_config):设置指定引脚为输入方向，上下拉电阻和感知状态。
 * nrf_gpio_pin_read        (uint32_t pin_number):读取指定引脚的电平状态，0代表低电平，1代表高电平
 * nrf_gpio_cfg             (uint32_t pin_number,
 *                           nrf_gpio_pin_dir_t dir,
 *                           nrf_gpio_pin_input_t input,
 *                           nrf_gpio_pin_pull_t pull,
 *                           nrf_gpio_pin_drive_t drive,
 *                           nrf_gpio_pin_sense_t sense):设置指定引脚的工作方式。PIN_CNF寄存器的任何位。
 * 
 */



//#if defined(__ARM_nRF52840__)
/**
 * @brief For TMK HHKB alt controller(ATMega32U4)
 *
 * row:     PB0-2
 * col:     PB3-5,6
 * key:     PD7(pull-uped)
 * prev:    PB7
 * power:   PD4(L:off/H:on)
 * row-ext: PC6,7 for HHKB JP(active low)
 */
static inline void KEY_ENABLE(void) 
{ 
    //(PORTB &= ~(1<<6)); 
    nrf_gpio_cfg_output((uint32_t)col_sel_pin);
    nrf_gpio_pin_clear((uint32_t)col_sel_pin); //Low(0) enables selected column
}
static inline void KEY_UNABLE(void) 
{ 
    //(PORTB |=  (1<<6)); 
    nrf_gpio_cfg_output((uint32_t)col_sel_pin);
    nrf_gpio_pin_set((uint32_t)col_sel_pin); 
}
static inline bool KEY_STATE(void) 
{ 
    //return (PIND & (1<<7)); 
    return nrf_gpio_pin_read((uint32_t)key_pin);
}
static inline void KEY_PREV_ON(void) 
{ 
    //(PORTB |=  (1<<7));
    nrf_gpio_cfg_output((uint32_t)hys_pin);
    nrf_gpio_pin_set((uint32_t)hys_pin);
}
static inline void KEY_PREV_OFF(void) 
{ 
    //(PORTB &= ~(1<<7)); 
    nrf_gpio_cfg_output((uint32_t)hys_pin);
    nrf_gpio_pin_clear((uint32_t)hys_pin);
}
#ifdef HHKB_POWER_SAVING
static inline void KEY_POWER_ON(void) {
    //DDRB = 0xFF; PORTB = 0x40;          // change pins output
    for (uint8_t i = 0; i < HHKB_PIN_NUM; i++) {
        nrf_gpio_cfg_output((uint32_t)hhkb_pin_array[i]);
        nrf_gpio_pin_clear((uint32_t)hhkb_pin_array[i]);
    }
    nrf_gpio_cfg_output((uint32_t)col_sel_pin);
    nrf_gpio_pin_set((uint32_t)col_sel_pin); 
    //DDRD |= (1<<4); PORTD |= (1<<4);    // MOS FET switch on
    nrf_gpio_cfg_output((uint32_t)power_pin);
    nrf_gpio_pin_set((uint32_t)power_pin); 
    /* Without this wait you will miss or get false key events. */
    //_delay_ms(5);                       // wait for powering up
    nrf_delay_ms((uint32_t)5);
}
static inline void KEY_POWER_OFF(void) {
    /* input with pull-up consumes less than without it when pin is open. */
    //DDRB = 0x00; PORTB = 0xFF;          // change pins input with pull-up
    for (uint8_t i = 0; i < HHKB_PIN_NUM; i++) {
        nrf_gpio_cfg_input((uint32_t)hhkb_pin_array[i], NRF_GPIO_PIN_PULLUP);
    }
    nrf_gpio_cfg_input((uint32_t)col_sel_pin, NRF_GPIO_PIN_PULLUP);
    //DDRD |= (1<<4); PORTD &= ~(1<<4);   // MOS FET switch off
    nrf_gpio_cfg_output((uint32_t)power_pin);
    nrf_gpio_pin_clear((uint32_t)power_pin); 
}
static inline bool KEY_POWER_STATE(void) 
{ 
    //return PORTD & (1<<4); 
    return nrf_gpio_pin_read((uint32_t)power_pin);
}
#else
static inline void KEY_POWER_ON(void) {}
static inline void KEY_POWER_OFF(void) {}
static inline bool KEY_POWER_STATE(void) { return true; }
#endif
static inline void KEY_INIT(void)
{
    /* row,col,prev: output */
    //DDRB  = 0xFF;
    //PORTB = 0x40;   // unable
    for (uint8_t i = 0; i < HHKB_PIN_NUM; i++) {
        nrf_gpio_cfg_output((uint32_t)hhkb_pin_array[i]);
        nrf_gpio_pin_clear((uint32_t)hhkb_pin_array[i]);
    }
    nrf_gpio_cfg_output((uint32_t)col_sel_pin);
    nrf_gpio_pin_set((uint32_t)col_sel_pin); 
    /* key: input with pull-up */
    //DDRD  &= ~0x80;
    //PORTD |=  0x80;
    nrf_gpio_cfg_input((uint32_t)key_pin, NRF_GPIO_PIN_PULLUP);
/**
#ifdef HHKB_JP
    // row extention for HHKB JP
    DDRC  |= (1<<6|1<<7);
    PORTC |= (1<<6|1<<7);
#else
    // input with pull up to save power 
    DDRC  &= ~(1<<6|1<<7);
    PORTC |=  (1<<6|1<<7);
#endif
 */
    KEY_UNABLE();
    KEY_PREV_OFF();

    KEY_POWER_OFF();
}
static inline void KEY_SELECT(uint8_t ROW, uint8_t COL)
{
    //PORTB = (PORTB & 0xC0) | (((COL) & 0x07)<<3) | ((ROW) & 0x07);
    // only need to change bit:0-5. (row0,row1,row2,col0,col1,col2)
    uint8_t OUT = (((COL) & 0x07)<<3) | ((ROW) & 0x07);
    for (uint8_t i = 0; i < HHKB_PIN_NUM-1; i++) {
        //nrf_gpio_cfg_output((uint32_t)hhkb_pin_array[i]);
        nrf_gpio_pin_write((uint32_t)hhkb_pin_array[i],(((uint32_t)OUT >> i) & 1UL));
    }
/**
#ifdef HHKB_JP
    if ((ROW) & 0x08) PORTC = (PORTC & ~(1<<6|1<<7)) | (1<<6);
    else              PORTC = (PORTC & ~(1<<6|1<<7)) | (1<<7);
#endif
 */
}

#endif
