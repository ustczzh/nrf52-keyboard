
#include "bat.h"


/**@brief Function for performing a battery measurement, and update the Battery Level characteristic in the Battery Service.
 */
void battery_level_update(nrf_saadc_value_t value, uint16_t size) {
    ret_code_t err_code;
    uint8_t    battery_level;

    uint32_t voltage = (value * 6 * 600 * 143 / 256 / 100 / size);
    NRF_LOG_INFO("Battery voltage: %d mV", voltage);

    if (voltage > 4200) {
        battery_level = 100;
    } else if (voltage > 4000) {
        battery_level = 82 + 18 * (voltage - 4000) / 200;
    } else if (voltage > 3800) {
        battery_level = 44 + 38 * (voltage - 3800) / 200;
    } else if (voltage > 3740) {
        battery_level = 20 + 24 * (voltage - 3740) / 160;
    } else if (voltage > 3680) {
        battery_level = 10 + (voltage - 3680) / 6;
    } else if (voltage > 3000) {
        battery_level = (voltage - 3000) / 68;
    } else {
        battery_level = 0;
    }

    err_code = ble_bas_battery_level_update(&m_bas, battery_level, BLE_CONN_HANDLE_ALL);
    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY) && (err_code != NRF_ERROR_RESOURCES) && (err_code != NRF_ERROR_FORBIDDEN) && (err_code != NRF_ERROR_INVALID_STATE) && (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)) {
        APP_ERROR_HANDLER(err_code);
    }
}

/**@brief Function for handling the Battery measurement timer timeout.
 *
 * @details This function will be called each time the battery level measurement timer expires.
 *
 * @param[in]   p_context   Pointer used for passing some arbitrary information (context) from the
 *                          app_start_timer() call to the timeout handler.
 */
static void battery_level_meas_timeout_handler(void *p_context) {
    UNUSED_PARAMETER(p_context);
#ifdef SLEEP_OFF_TIMEOUT
    if (power_save_counter++ > SLEEP_OFF_TIMEOUT / 2) {
        sleep_mode_enter();
    }
#endif
#ifdef KBD_WDT_ENABLE
    nrfx_wdt_channel_feed(m_channel_id);
#endif
    adc_start();
}

void reset_power_save_counter() {
#ifdef SLEEP_OFF_TIMEOUT
    power_save_counter = 0;
#endif
}

/**@brief Function for the Timer initialization.
 */
static void bat_timers_create(void) {
    ret_code_t err_code;

    // Create battery timer.
    err_code = app_timer_create(&m_battery_timer_id, APP_TIMER_MODE_REPEATED, battery_level_meas_timeout_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for starting timers.
 */
static void bat_timers_start(void) {
    ret_code_t err_code;

    err_code = app_timer_start(m_battery_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
static void sleep_mode_enter(void) {
#ifdef IS31FL3737
    i2c_stop();
#endif
    NRF_LOG_INFO("Sleep mode");
    ret_code_t err_code;

    static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
    static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        nrf_gpio_cfg_output(row_pins[i]);
        nrf_gpio_pin_clear(row_pins[i]);
    }
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_cfg_sense_input(col_pins[i], NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    }

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    while (1) {
    }
    APP_ERROR_CHECK(err_code);
}

void deep_sleep_mode_enter(void) {
#ifdef IS31FL3737
    i2c_stop();
#endif
    NRF_LOG_INFO("Deep sleep mode");
    ret_code_t err_code;

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    while (1) {
    }
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing power management.
 */
static void power_management_init(void) {
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);

    // Lotlab has this.
    //sd_power_dcdc_mode_set(1);
}

/**@brief Function for handling the idle state (main loop).
 *
 * @details If there is no pending log operation, then sleep until next the next event occurs.
 */
void idle_state_handle(void) {
    if (NRF_LOG_PROCESS() == false) {
        nrf_pwr_mgmt_run();
    }
}