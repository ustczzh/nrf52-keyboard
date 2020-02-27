# 配置项：主控芯片类型
# 可选：nrf52840
NRF_CHIP := nrf52840
PLATFORM := nrf5

# 配置项：功能选项
# 关于更多的可配置项目，请参考doc目录下的相应文档
BOOTMAGIC_ENABLE = yes	# 启用Bootmagic
NKRO_ENABLE = yes	    # 启用USB的全键无冲功能
USB_6KRO_ENABLE = yes   # 启用USB的六键无冲功能
UNIMAP_ENABLE = yes
ACTIONMAP_ENABLE = yes  
MOUSEKEY_ENABLE = yes   # 启用鼠标键功能
EXTRAKEY_ENABLE = yes   # 启用媒体键功能

#KEYBOARD_FRAMEWORK = mx
KEYBOARD_FRAMEWORK = topre

########## STOP HERE ##########
# 除非你知道下面这些配置项是干什么的，否则不要去动它# 此工程的根目录
ROOT_DIR := ../../..

# 配置文件文件名
CONFIG_H = $(ROOT_DIR)/project/config.h

# unimap
SRC_FILES += $(ROOT_DIR)/unimap/unimap_hhkb_zzh.c
INC_FOLDERS += $(ROOT_DIR)/unimap

SDK_ROOT := $(ROOT_DIR)/SDK

APP_MAIN_DIR   := $(ROOT_DIR)/application/main
APP_PROJ_DIR   := $(APP_MAIN_DIR)/project
APP_SRC_DIR    := $(APP_MAIN_DIR)/src

KEY_MAIN_DIR   := $(ROOT_DIR)/keyboard/hhkb
KEY_PROJ_DIR   := $(KEY_MAIN_DIR)/project
KEY_SRC_DIR    := $(KEY_MAIN_DIR)
KEY_COMMON_DIR := $(KEY_MAIN_DIR)/common
KEY_COMMON_PLATFORM_DIR := $(KEY_MAIN_DIR)/common/$(PLATFORM)

TMK_CORE_DIR   := $(ROOT_DIR)/tmk/tmk_core
TMK_COMMON_DIR := $(TMK_CORE_DIR)/common

all: default

include $(APP_PROJ_DIR)/tmk.mk
include $(APP_PROJ_DIR)/kbd.mk
include $(APP_PROJ_DIR)/driver.mk
include $(APP_PROJ_DIR)/app.mk