
#include "host_driver.h"

host_driver_t *nrf5_ble_driver(void);

/**@brief Function for starting advertising.
 */
void advertising_start(bool erase_bonds);
void advertising_without_whitelist(void);
void restart_advertising_id(uint8_t id);
void ble_service_init(void);
void ble_disconnect(void);
// void send_midis(void);
