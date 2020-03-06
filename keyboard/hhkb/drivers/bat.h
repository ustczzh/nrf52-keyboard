#ifndef BAT_H
#define BAT_H

#include "nrf_drv_saadc.h"

#include "app_timer.h"
#include "ble_bas.h"

#ifdef SLEEP_OFF_TIMEOUT
extern uint16_t power_save_counter;
#endif

#define BATTERY_LEVEL_MEAS_INTERVAL APP_TIMER_TICKS(2000) /**< Battery level measurement interval (ticks). */

APP_TIMER_DEF(m_battery_timer_id);  /**< Battery timer. */
BLE_BAS_DEF(m_bas);                 /**< Structure used to identify the battery service. */

void battery_level_update(nrf_saadc_value_t value, uint16_t size);

void reset_power_save_counter(void);
// Create battery timer
void bat_timers_create(void);
// Start battery timer
void bat_timers_start(void);

void sleep_mode_enter(void);
void deep_sleep_mode_enter(void);
void power_management_init(void);
void idle_state_handle(void);

#endif