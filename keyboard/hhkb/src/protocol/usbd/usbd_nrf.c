#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nrf.h"
#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_drv_power.h"

#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_hid_mouse.h"
#include "app_usbd_hid_kbd.h"
#include "app_error.h"

/**
 * @brief Enable USB power detection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

/**
 * @brief Enable HID mouse class
 */
#define CONFIG_HAS_MOUSE    0

/**
 * @brief Enable HID keyboard class
 */
#define CONFIG_HAS_KBD      1

/**
 * @brief Mouse button count
 */
#define CONFIG_MOUSE_BUTTON_COUNT 5

/**
 * @brief Mouse speed (value sent via HID when board button is pressed).
 */
#define CONFIG_MOUSE_MOVE_STEP (3)

/**
 * @brief Mouse move repeat time in milliseconds
 */
#define CONFIG_MOUSE_MOVE_TIME_MS (5)

/**
 * @brief Letter to be sent on LETTER button
 *
 * @sa BTN_KBD_LETTER
 */
#define CONFIG_KBD_LETTER APP_USBD_HID_KBD_G

/**
 * @brief Propagate SET_PROTOCOL command to other HID instance
 */
#define PROPAGATE_PROTOCOL  1

/**
 * @brief USB composite interfaces
 */
#define APP_USBD_INTERFACE_MOUSE 0
#define APP_USBD_INTERFACE_KBD   1

/**
 * @brief User event handler, HID keyboard
 */
static void hid_kbd_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_hid_user_event_t event);

/*lint -save -e26 -e64 -e123 -e505 -e651*/

/**
 * @brief Global HID keyboard instance
 */
APP_USBD_HID_KBD_GLOBAL_DEF(m_app_hid_kbd,
                            APP_USBD_INTERFACE_KBD,
                            NRF_DRV_USBD_EPIN2,
                            hid_kbd_user_ev_handler,
                            APP_USBD_HID_SUBCLASS_BOOT
);

static void kbd_status(void)
{
#if HAS_LED
    if(app_usbd_hid_kbd_led_state_get(&m_app_hid_kbd, APP_USBD_HID_KBD_LED_NUM_LOCK))
    {
        bsp_board_led_on(LED_NUMLOCK);
    }
    else
    {
        bsp_board_led_off(LED_NUMLOCK);
    }

    if(app_usbd_hid_kbd_led_state_get(&m_app_hid_kbd, APP_USBD_HID_KBD_LED_CAPS_LOCK))
    {
        bsp_board_led_on(LED_CAPSLOCK);
    }
    else
    {
        bsp_board_led_off(LED_CAPSLOCK);
    }
#endif
}

/**
 * @brief Class specific event handler.
 *
 * @param p_inst    Class instance.
 * @param event     Class specific event.
 * */
static void hid_mouse_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_user_event_t event)
{
    UNUSED_PARAMETER(p_inst);
    switch (event) {
        case APP_USBD_HID_USER_EVT_OUT_REPORT_READY:
            /* No output report defined for HID mouse.*/
            break;
        case APP_USBD_HID_USER_EVT_IN_REPORT_DONE:
            break;
        case APP_USBD_HID_USER_EVT_SET_BOOT_PROTO:
            UNUSED_RETURN_VALUE(hid_mouse_clear_buffer(p_inst));
#if PROPAGATE_PROTOCOL
            hid_kbd_on_set_protocol(&m_app_hid_kbd, APP_USBD_HID_USER_EVT_SET_BOOT_PROTO);
#endif
            break;
        case APP_USBD_HID_USER_EVT_SET_REPORT_PROTO:
            UNUSED_RETURN_VALUE(hid_mouse_clear_buffer(p_inst));
#if PROPAGATE_PROTOCOL
            hid_kbd_on_set_protocol(&m_app_hid_kbd, APP_USBD_HID_USER_EVT_SET_REPORT_PROTO);
#endif
            break;
        default:
            break;
    }
}

/**
 * @brief Class specific event handler.
 *
 * @param p_inst    Class instance.
 * @param event     Class specific event.
 * */
static void hid_kbd_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_hid_user_event_t event)
{
    UNUSED_PARAMETER(p_inst);
    switch (event) {
        case APP_USBD_HID_USER_EVT_OUT_REPORT_READY:
            /* Only one output report IS defined for HID keyboard class. Update LEDs state. */
            kbd_status();
            break;
        case APP_USBD_HID_USER_EVT_IN_REPORT_DONE:
            break;
        case APP_USBD_HID_USER_EVT_SET_BOOT_PROTO:
            UNUSED_RETURN_VALUE(hid_kbd_clear_buffer(p_inst));
#if PROPAGATE_PROTOCOL
            hid_mouse_on_set_protocol(&m_app_hid_mouse, APP_USBD_HID_USER_EVT_SET_BOOT_PROTO);
#endif
            break;
        case APP_USBD_HID_USER_EVT_SET_REPORT_PROTO:
            UNUSED_RETURN_VALUE(hid_kbd_clear_buffer(p_inst));
#if PROPAGATE_PROTOCOL
            hid_mouse_on_set_protocol(&m_app_hid_mouse, APP_USBD_HID_USER_EVT_SET_REPORT_PROTO);
#endif
            break;
        default:
            break;
    }
}


/**
 * @brief USBD library specific event handler.
 *
 * @param event     USBD library event.
 * */
static void usbd_user_ev_handler(app_usbd_event_type_t event)
{
    switch (event)
    {
        case APP_USBD_EVT_DRV_SOF:
            break;
        case APP_USBD_EVT_DRV_SUSPEND:
            app_usbd_suspend_req(); // Allow the library to put the peripheral into sleep mode
#if HAS_LED
            bsp_board_leds_off();
#endif
            break;
        case APP_USBD_EVT_DRV_RESUME:
#if HAS_LED
            bsp_board_led_on(LED_USB_START);
            kbd_status(); /* Restore LED state - during SUSPEND all LEDS are turned off */
#endif
            break;
        case APP_USBD_EVT_STARTED:
#if HAS_LED
            bsp_board_led_on(LED_USB_START);
#endif
            break;
        case APP_USBD_EVT_STOPPED:
            app_usbd_disable();
#if HAS_LED
            bsp_board_leds_off();
#endif
            break;
        case APP_USBD_EVT_POWER_DETECTED:
            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }
            break;
        case APP_USBD_EVT_POWER_REMOVED:
            app_usbd_stop();
            break;
        case APP_USBD_EVT_POWER_READY:
            app_usbd_start();
            break;
        default:
            break;
    }
}


static void bsp_event_callback(bsp_event_t ev)
{
    switch ((unsigned int)ev)
    {
        case CONCAT_2(BSP_EVENT_KEY_, BTN_KBD_SHIFT):
            UNUSED_RETURN_VALUE(app_usbd_hid_kbd_modifier_state_set(&m_app_hid_kbd, APP_USBD_HID_KBD_MODIFIER_LEFT_SHIFT, true));
            break;
        case CONCAT_2(BSP_USER_EVENT_RELEASE_, BTN_KBD_SHIFT):
            UNUSED_RETURN_VALUE(app_usbd_hid_kbd_modifier_state_set(&m_app_hid_kbd, APP_USBD_HID_KBD_MODIFIER_LEFT_SHIFT, false));
            break;

        case CONCAT_2(BSP_EVENT_KEY_, BTN_KBD_LETTER):
            UNUSED_RETURN_VALUE(app_usbd_hid_kbd_key_control(&m_app_hid_kbd, CONFIG_KBD_LETTER, true));
            break;
        case CONCAT_2(BSP_USER_EVENT_RELEASE_, BTN_KBD_LETTER):
            UNUSED_RETURN_VALUE(app_usbd_hid_kbd_key_control(&m_app_hid_kbd, CONFIG_KBD_LETTER, false));
            break;

        default:
            return; // no implementation needed
    }
}


int main(void)
{
    ret_code_t ret;
    static const app_usbd_config_t usbd_config = {
        .ev_state_proc = usbd_user_ev_handler,
    };

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);

    nrf_drv_clock_lfclk_request(NULL);
    while(!nrf_drv_clock_lfclk_is_running())
    {
        /* Just waiting */
    }

    ret = app_usbd_init(&usbd_config);
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_inst_mouse;
#if CONFIG_HAS_MOUSE
    class_inst_mouse = app_usbd_hid_mouse_class_inst_get(&m_app_hid_mouse);
#else
    class_inst_mouse = app_usbd_dummy_class_inst_get(&m_app_mouse_dummy);
#endif
    ret = app_usbd_class_append(class_inst_mouse);
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_inst_kbd;
#if CONFIG_HAS_KBD
    class_inst_kbd = app_usbd_hid_kbd_class_inst_get(&m_app_hid_kbd);
#else
    class_inst_kbd = app_usbd_dummy_class_inst_get(&m_app_kbd_dummy);
#endif
    ret = app_usbd_class_append(class_inst_kbd);
    APP_ERROR_CHECK(ret);

    NRF_LOG_INFO("USBD HID composite example started.");
    
    if (USBD_POWER_DETECTION)
    {
        ret = app_usbd_power_events_enable();
        APP_ERROR_CHECK(ret);
    }
    else
    {
        NRF_LOG_INFO("No USB power detection enabled\r\nStarting USB now");

        app_usbd_enable();
        app_usbd_start();
    }

    while (true)
    {
        while (app_usbd_event_queue_process())
        {
            /* Nothing to do */
        }
#if NRF_CLI_ENABLED
        nrf_cli_process(&m_cli_uart);
#endif

        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
        /* Sleep CPU only if there was no interrupt since last loop processing */
        __WFE();
    }
}
