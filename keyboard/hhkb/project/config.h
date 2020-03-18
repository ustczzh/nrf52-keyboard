/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2019 Jim Jiang <jim@lotlab.org>

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

#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#include "xenon.h"

/* USB和蓝牙的显示参数 */
#define VENDOR_ID 0x1209 /* USB VID */
#define PRODUCT_ID 0x0514 /* USB PID */
#define CONF_VENDOR_ID 0x0114 /* 配置项目内显示的VendorID */
#define CONF_PRODUCT_ID 0x0514 /* 配置项目内显示的ProductID */
#define DEVICE_VER 0x0001 /* 硬件版本 */
#define MANUFACTURER "ZZZ" /* 硬件制造商，用于蓝牙显示 */
#define PRODUCT_NAME "BLE5 HHKB" /* 硬件名称，用于USB和蓝牙显示 */
// #define MACADDR_SEPRATOR '_' /* 蓝牙名称后地址的分隔符。若不设置则不显示蓝牙名称后面的地址 */

/* 蓝牙 */
#define BLUETOOTH_ENABLE

/* USB HID report parameter */
// #define KEYBOARD_EPSIZE 8 /* 键盘上传端点大小，请不要修改 */
#define NKRO_EPSIZE 28 /* 键盘NKRO端点大小，请不要修改 */
// #define BLE_NKRO
// Force NKRO
// #define FORCE_NKRO
// Enable watchdog
// #define KBD_WDT_ENABLE
// #define MAX_ENDPOINTS 8
// #define NKRO_ENABLE
// #define MOUSE_ENABLE
// #define EXTRAKEY_ENABLE

// 定义Bootmagic按键
//#define BOOTMAGIC_ENABLE
// #define BOOTMAGIC_KEY_BOOT KC_U /* 开机 */
// #define BOOTMAGIC_KEY_ERASE_BOND KC_E /* 删除所有绑定 */

// 键盘省电参数
#define SLEEP_SLOW_TIMEOUT 15 // 键盘闲置多久后转入慢速扫描模式 (s)
#define SLEEP_OFF_TIMEOUT 600 // 键盘闲置多久后转入自动关机 (s)
#define KEYBOARD_SCAN_INTERVAL 1 // 键盘最小时间单位TICK (ms)
#define KEYBOARD_FAST_SCAN_INTERVAL 10 // 通常模式下，多久扫描一次键盘 (ms)
#define KEYBOARD_SLOW_SCAN_INTERVAL 100 // 慢速模式下，多久扫描一次键盘 (ms)
// #define LED_AUTOOFF_TIME 5 /* LED自动熄灭时长(s)，设为0则不自动熄灭 */

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

// 电量检测配置
#define BATTERY_ADC_PIN NRF_SAADC_INPUT_AIN3 // 电量检测引脚

// 充电检测配置
// #define PIN_CHARGING !UCC1 // CH554的充电检测。当UCC1拉低时表示正在充电
// #define PIN_STANDBY !UCC2 // CH554的充电检测。当UCC2拉低时表示充电完成。若不配置则只使用PIN_CHARGING作为是否充电的检测标志

// for HHKB only
//#define HHKB_JP
#define HHKB_POWER_SAVING

// 按键阵列配置
/* keyboard matrix size */
#ifdef HHKB_JP
#   define MATRIX_ROWS 16
#else
#   define MATRIX_ROWS 8
#endif
#define MATRIX_COLS 8

static const uint8_t power_pin = PIN_D8;
static const uint8_t key_pin = PIN_D6;
static const uint8_t hys_pin = PIN_D5;
static const uint8_t row0_pin = PIN_D4;
static const uint8_t row1_pin = PIN_D3;
static const uint8_t row2_pin = PIN_D2;
static const uint8_t col0_pin = PIN_A3;
static const uint8_t col1_pin = PIN_A2;
static const uint8_t col2_pin = PIN_A1;
static const uint8_t col_sel_pin = PIN_A0;
/**
 * @brief HHKB pin for nrf52840
 * row:     11,12,13
 * col:     14,15,16,17
 * key:     18(pull-uped)
 * prev:    19
 * power:   20(L:off/H:on)
 */
#define HHKB_PIN_NUM 7
static const uint8_t hhkb_pin_array[HHKB_PIN_NUM] = {           \
    row0_pin, row1_pin, row2_pin, col0_pin, col1_pin, col2_pin, \
    hys_pin };



// NRF52840 pin map: (((port) << 5) | ((pin) & 0x1F))
#define MATRIX_ROW_PINS \
    { row0_pin, row1_pin, row2_pin }
#define MATRIX_COL_PINS \
    { col0_pin, col1_pin, col2_pin }


#define PERMISSVIE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 300
#define ONESHOT_TIMEOUT 300

#endif
