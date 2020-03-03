# 流程图

## 模板

```flow
st=>start: Start
e=>end
op1=>operation: keyboard_setup
...matrix_setup
keyboard_init
...timer_init
...matrix_init
...ps2_mouse_init
...bootmagic
log_init
timers_init
...app_timer_init
usb_keyboard_init
...app_usbd_init
...app_usbd_hid_generic_class_inst_get
...app_usbd_class_append
...app_usbd_power_events_enable
ble_service_init
...adc_init
...bat_timers_init
...power_management_init
...ble_stack_init
......nrf_sdh_enable_request
......nrf_sdh_ble_default_cfg_set
......nrf_sdh_ble_enable
......NRF_SDH_BLE_OBSERVER
...gap_params_init
...gatt_init
...services_init
......qwr_init
......dis_init
......dfu_init
......bas_init
......hids_kbd_init
...advertising_init
...conn_params_init
...peer_manager_init
...wdt_init
...timers_start
app_timer_create
app_timer_start
op2=>operation: advertising_start
op3=>operation: app_sched_execute
execute_event
idle_state_handle
...nrf_pwr_mgmt_run


cond1=>condition: NRF_USBD->ENABLE
cond2=>condition: while(true)
cond3=>condition: app_usbd_event_queue_process
cond4=>condition: loop

sub1=>subroutine: My Subroutine
io=>inputoutput: catch something...

st->op1->cond1
cond1(yes)->op2->cond2
cond1(no)->cond2

cond2(yes)->cond3
cond3(no,top)->cond3
cond3(yes,bottom)->op3(left)->cond2

```


```flow
op1=>operation: timers_init
...app_timer_init
power_management_init
...nrf_pwr_mgmt_init
...sd_power_dcdc_mode_set(1)
ble_stack_init
...nrf_sdh_enable_request
...nrf_sdh_ble_default_cfg_set
...nrf_sdh_ble_enable
...NRF_SDH_BLE_OBSERVER
scheduler_init
...APP_SCHED_INIT
services_init
...ble_services_init
......peer_manager_init
......gap_params_init
......gatt_init
......advertising_init
......qwr_init
......dis_init
......dfu_init
......conn_params_init
...battery_service_init
......bas_init
...hid_service_init
......hids_init
......buffer_init
...adc_init
......app_timer_create
ble_keyboard_init
...keyboard_setup
......matrix_setup
...keyboard_led_init
...storage_init
...usb_comm_init
...keyboard_init
...host_set_driver
...keyboard_timer_init
...keyboard_wdt_init
timers_start
...ble_keyboard_timer_start
...usb_comm_timer_start
...adc_timer_start
advertising_start
op2=>operation: idle_state_handle
...app_sched_execute
...execute_event
...nrf_pwr_mgmt_run

cond1=>condition: while(true)

st=>start: Start
e=>end

st->op1->cond1
cond1(yes)->op2(right)->cond1
```

