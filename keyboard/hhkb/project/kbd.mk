
# project specific files
SRC_FILES +=  \
    $(KEY_SRC_DIR)/driver/adc/adc.c \
    $(KEY_SRC_DIR)/bat.c \
    $(KEY_SRC_DIR)/host_driver.c \
    $(KEY_SRC_DIR)/outputselect.c \
    $(KEY_SRC_DIR)/tmk/keyboard_timer.c \
    $(KEY_SRC_DIR)/suspend.c \
	$(KEY_SRC_DIR)/adc.c \
	$(KEY_SRC_DIR)/outputselect.c \
	$(KEY_SRC_DIR)/main.c \
	$(KEY_SRC_DIR)/outputselect.c \
	$(KEY_SRC_DIR)/usb/nrf5_usb.c \
	$(KEY_SRC_DIR)/usb/fixed/app_usbd_hid_generic.c \
	$(KEY_SRC_DIR)/ble/ble_service.c \
	$(KEY_SRC_DIR)/ble/ble_hids_service.c \

    

INC_FOLDERS +=  \
    $(KEY_SRC_DIR)
    $(KEY_SRC_DIR)/drivers
    $(KEY_SRC_DIR)/drivers/adc
    $(KEY_SRC_DIR)/matrix
    $(KEY_SRC_DIR)/pca10056/blank/config
    $(KEY_SRC_DIR)/project
    $(KEY_SRC_DIR)/protocol/ble
    $(KEY_SRC_DIR)/protocol/usb
    $(KEY_SRC_DIR)/unimap \
    $(KEY_SRC_DIR)/tmk \

# Version string
VERSION := $(shell ((git describe --always --abbrev=8 || echo '00000000') | sed "s/.*-g//g" ) 2> /dev/null)
TMK_COMMON_DEFS += -DVERSION=$(VERSION)
TMK_COMMON_DEFS += -DBUILD_TIME=$(shell date +%s)
