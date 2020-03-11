#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "nrf_section.h"

#include "config.h"
#include "section.h"

#ifdef ACTIONMAP_ENABLE
#define SINGLE_KEY_SIZE 2
#else
#define SINGLE_KEY_SIZE 1
#endif

#define MAX_LAYER 8 // 存储区域中最大层数
#define MAX_FN_KEYS 32 // 存储区域最大Fn数目
#define MAX_MACRO_SIZE 256 // 宏存储区域最大容量
#define FILE_ID 0x0001

#define KEYMAP_ROW_SIZE   (MATRIX_COLS * SINGLE_KEY_SIZE)
#define KEYMAP_LAYER_SIZE (MATRIX_ROWS * KEYMAP_ROW_SIZE)

/**
 * @brief 存储类型
 * 
 */
enum record_type {
    RECORD_KEYMAP, // Keymap
    RECORD_FN,     // Fn 区域
    RECORD_MACRO,  // 自定义宏
    RECORD_CONFIG  // 配置区域
};

void storage_stat(void);
void storage_init(void);
void storage_read(uint8_t mask);
bool storage_update(uint8_t mask);
uint16_t storage_read_data( enum record_type type, uint16_t offset, uint16_t len, uint8_t* data);
uint16_t storage_write_data(enum record_type type, uint16_t offset, uint16_t len, uint8_t* data);

// 若启用了BOOTMAGIC_ENABLE则自动启用SAVE_CONFIG
#ifdef BOOTMAGIC_ENABLE
#define SAVE_CONFIG
#endif

#ifdef SAVE_CONFIG
extern uint8_t config_block[];

#endif
