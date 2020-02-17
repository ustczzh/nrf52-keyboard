ifndef TMK_CORE_DIR
    TMK_CORE_DIR = ../../../tmk/tmk_core
endif

ifndef APP_SRC_DIR
    APP_SRC_DIR := ../src
endif

ifndef ROOT_DIR
    ROOT_DIR := ../../..
endif

ifndef SDK_ROOT
    SDK_ROOT := $(ROOT_DIR)/SDK
endif

# project specific files
SRC_FILES +=  \
    $(APP_SRC_DIR)/keyboard/$(KEYBOARD_FRAMEWORK)/keyboard_matrix.c \
    $(APP_SRC_DIR)/keyboard/common/host_driver.c \
    $(APP_SRC_DIR)/keyboard/common/ble_keyboard.c \
    $(APP_SRC_DIR)/tmk/keyboard_timer.c \
    $(APP_SRC_DIR)/tmk/glue_layer.c \
    $(APP_SRC_DIR)/keyboard/common/keyboard_fn.c \
    $(APP_SRC_DIR)/keyboard/common/keyboard_led.c \
    $(APP_SRC_DIR)/keyboard/common/passkey.c \
    $(APP_SRC_DIR)/keyboard/common/keyboard_bootmagic.c \
    $(APP_SRC_DIR)/keyboard/common/data_storage.c \
    $(APP_SRC_DIR)/protocol/common/hid_configuration.c \
    $(APP_SRC_DIR)/keyboard/common/sleep_reason.c \
    $(APP_SRC_DIR)/keyboard/common/keyboard_evt.c \
    $(APP_SRC_DIR)/keyboard/common/store_config.c \
    $(APP_SRC_DIR)/protocol/common/usb_comm.c \
    $(APP_SRC_DIR)/protocol/common/ble_comm.c \
    $(APP_SRC_DIR)/keyboard/common/macro_player.c \
    $(APP_SRC_DIR)/keyboard/common/power_save.c \
    $(APP_SRC_DIR)/keyboard/common/adc_convert.c 

INC_FOLDERS +=  \
    $(APP_SRC_DIR)/keyboard/$(KEYBOARD_FRAMEWORK) \
    $(APP_SRC_DIR)/keyboard/common \
    $(APP_SRC_DIR)/tmk \
    $(APP_SRC_DIR)/protocol \
    $(APP_SRC_DIR)/ble

# Version string
VERSION := $(shell ((git describe --always --abbrev=8 || echo '00000000') | sed "s/.*-g//g" ) 2> /dev/null)
OPT_DEFS += -DVERSION=$(VERSION)
OPT_DEFS += -DBUILD_TIME=$(shell date +%s)

# enable GPIO as RESET PIN
ifeq (yes,$(strip $(CONFIG_GPIO_AS_PINRESET)))
    OPT_DEFS += -DCONFIG_GPIO_AS_PINRESET
endif

include $(APP_PROJ_DIR)/tmk.mk
include $(APP_PROJ_DIR)/driver.mk
include $(APP_PROJ_DIR)/app.mk