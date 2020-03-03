/*
Copyright 2017 Priyadi Iman Nurcahyo
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "outputselect.h"

//#include "nrf.h"
//#include "nrf_gpio.h"
//#include "nrf_drv_power.h"
//#include "nrf_drv_clock.h"
//#include "app_timer.h"

#include "host.h"
#include "nrf5_usb.h"
#include "ble_service.h"

uint8_t desired_output = OUTPUT_DEFAULT;

/** \brief Set Output
 *
 * FIXME: Needs doc
 */
void set_output(uint8_t output) {
    switch (output) {
        case OUTPUT_NONE:
            host_set_driver(0);
            break;
        case OUTPUT_USB:
            host_set_driver(nrf5_usb_driver());
            // host_set_driver(0);
            break;
        case OUTPUT_BLUETOOTH:
            host_set_driver(nrf5_ble_driver());
            break;
    }
    set_output_user(output);
    desired_output = output;
}

/** \brief Set Output User
 *
 * FIXME: Needs doc
 */
__attribute__((weak)) void set_output_user(uint8_t output) {}

/** \brief Auto Detect Output
 *
 * FIXME: Needs doc
 */
// uint8_t auto_detect_output(void) {
//     if (USB_DeviceState == DEVICE_STATE_Configured) {
//         return OUTPUT_USB;
//     }

// #ifdef BLUETOOTH_ENABLE
//     return OUTPUT_BLUETOOTH; // should check if BT is connected here
// #endif

//     return OUTPUT_NONE;
// }

/** \brief Where To Send
 *
 * FIXME: Needs doc
 */
uint8_t where_to_send(void) {
    // if (desired_output == OUTPUT_AUTO) {
    //     return auto_detect_output();
    // }
    return desired_output;
}