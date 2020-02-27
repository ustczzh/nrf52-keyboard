ifndef ROOT_DIR
    ROOT_DIR := ../../..
endif

ifndef SDK_ROOT
    SDK_ROOT := $(ROOT_DIR)/SDK
endif

ifndef TMK_CORE_DIR
    TMK_CORE_DIR = $(ROOT_DIR)/tmk/tmk_core
endif

ifndef APP_SRC_DIR
    APP_SRC_DIR := ../
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/mousekey.c
    TMK_COMMON_DEFS += -DMOUSEKEY_ENABLE
    TMK_COMMON_DEFS += -DMOUSE_ENABLE
endif

ifeq ($(strip $(EXTRAKEY_ENABLE)), yes)
    TMK_COMMON_DEFS += -DEXTRAKEY_ENABLE
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    TMK_COMMON_DEFS += -DCONSOLE_ENABLE
else
    TMK_COMMON_DEFS += -DNO_PRINT
    TMK_COMMON_DEFS += -DNO_DEBUG
endif
ifeq ($(strip $(COMMAND_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/command.c
    TMK_COMMON_DEFS += -DCOMMAND_ENABLE
endif

ifeq ($(strip $(NKRO_ENABLE)), yes)
    TMK_COMMON_DEFS += -DNKRO_ENABLE
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(USB_6KRO_ENABLE)), yes)
    TMK_COMMON_DEFS += -DUSB_6KRO_ENABLE
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