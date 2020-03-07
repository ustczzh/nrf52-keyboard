#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "nrf_section.h"

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

void record_read(uint8_t mask);
void record_init(void);
bool record_write(uint8_t mask);
uint16_t record_read_data( enum record_type type, uint16_t offset, uint16_t len, uint8_t* data);
uint16_t record_write_data(enum record_type type, uint16_t offset, uint16_t len, uint8_t* data);

// 若启用了BOOTMAGIC_ENABLE则自动启用SAVE_CONFIG
#ifdef BOOTMAGIC_ENABLE
#define SAVE_CONFIG
#endif

#ifdef SAVE_CONFIG
extern uint8_t config_block[];

/**
 * @brief 配置记录区域
 * 
 */
struct config_section {
    /**
     * @brief 数据长度
     * 
     */
    uint8_t len;
    /**
     * @brief 数据指针
     * 
     */
    uint8_t* data;
};

/**
 * @brief 定义一个储存区
 * 
 */
#define CONFIG_SECTION_DEF() NRF_SECTION_DEF(config_def, struct config_section)
/**
 * @brief 定义一块数据记录区域
 * 
 */
#define CONFIG_SECTION(name, length) NRF_SECTION_ITEM_REGISTER(config_def, struct config_section) name = { .len = length };
#define CONFIG_SECTION_COUNT NRF_SECTION_ITEM_COUNT(config_def, struct config_section)
#define CONFIG_SECTION_GET(i) (NRF_SECTION_ITEM_GET(config_def, struct config_section, i))

#endif
