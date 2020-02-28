
# project specific files
SRC_FILES +=  \
	$(KEY_SRC_DIR)/main.c \
    $(KEY_SRC_DIR)/drivers/adc/adc.c \
    $(KEY_SRC_DIR)/drivers/bat.c \
    $(KEY_SRC_DIR)/matrix/hhkb_matrix.c \
	$(KEY_SRC_DIR)/protocol/usb/nrf5_usb.c \
	$(KEY_SRC_DIR)/protocol/usb/fixed/app_usbd_hid_generic.c \
	$(KEY_SRC_DIR)/protocol/ble/ble_service.c \
	$(KEY_SRC_DIR)/protocol/ble/ble_hids_service.c \
    $(KEY_COMMON_DIR)/outputselect.c \
	$(KEY_COMMON_PLATFORM_DIR)/i2c_master.c \
	$(KEY_COMMON_PLATFORM_DIR)/suspend.c \
	$(KEY_COMMON_PLATFORM_DIR)/timer.c \
	$(KEY_COMMON_PLATFORM_DIR)/bootloader.c \
    $(KEY_COMMON_PLATFORM_DIR)/eeprom.c


INC_FOLDERS +=  \
    $(KEY_COMMON_DIR) \
    $(KEY_COMMON_PLATFORM_DIR) \
    $(KEY_SRC_DIR) \
    $(KEY_SRC_DIR)/drivers \
    $(KEY_SRC_DIR)/drivers/adc \
    $(KEY_SRC_DIR)/matrix \
    $(KEY_SRC_DIR)/pca10056/blank/config \
    $(KEY_SRC_DIR)/project \
    $(KEY_SRC_DIR)/protocol/ble \
    $(KEY_SRC_DIR)/protocol/usb \
    $(KEY_SRC_DIR)/unimap \
    $(KEY_SRC_DIR)/tmk

# Version string
VERSION := $(shell ((git describe --always --abbrev=8 || echo '00000000') | sed "s/.*-g//g" ) 2> /dev/null)
TMK_COMMON_DEFS += -DVERSION=$(VERSION)
TMK_COMMON_DEFS += -DBUILD_TIME=$(shell date +%s)
