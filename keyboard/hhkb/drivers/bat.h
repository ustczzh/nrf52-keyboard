
#include <stdint.h>
#include <string.h>

#include "nrf_gpio.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_power.h"
#include "nrfx_saadc.h"

#include "app_timer.h"
#include "adc.h"
#include "ble_bas.h"

#ifdef SLEEP_OFF_TIMEOUT
static uint16_t power_save_counter = 0;
#endif

#define BATTERY_LEVEL_MEAS_INTERVAL APP_TIMER_TICKS(2000) /**< Battery level measurement interval (ticks). */

APP_TIMER_DEF(m_battery_timer_id);  /**< Battery timer. */
BLE_BAS_DEF(m_bas);                 /**< Structure used to identify the battery service. */

static void sleep_mode_enter(void);

void idle_state_handle(void);
void deep_sleep_mode_enter(void);
void reset_power_save_counter(void);
void battery_level_update(nrf_saadc_value_t value, uint16_t size);
