PROJECT_NAME     := ble_app_hids_keyboard_pca10056_s140
TARGETS          := nrf52_kbd

include $(KEY_PROJ_DIR)/nrf52840.mk

ifndef OUTPUT_DIRECTORY
	OUTPUT_DIRECTORY := _build
endif

ifndef TEMPLATE_PATH
	TEMPLATE_PATH := $(ROOT_DIR)/template
endif

ifndef NRF_PACKAGE_NAME
	NRF_PACKAGE_NAME := $(OUTPUT_DIRECTORY)/$(TARGETS)_$(VERSION).zip
endif

$(OUTPUT_DIRECTORY)/$(TARGETS).out: \
	LINKER_SCRIPT  := $(KEY_SRC_DIR)/pca10056/blank/armgcc/$(LD_NAME)

# Source files common to all targets
SRC_FILES += \
	$(SDK_ROOT)/components/ble/ble_advertising/ble_advertising.c \
	$(SDK_ROOT)/components/ble/ble_link_ctx_manager/ble_link_ctx_manager.c \
	$(SDK_ROOT)/components/ble/ble_services/ble_bas/ble_bas.c \
	$(SDK_ROOT)/components/ble/ble_services/ble_dfu/ble_dfu.c \
	$(SDK_ROOT)/components/ble/ble_services/ble_dfu/ble_dfu_bonded.c \
	$(SDK_ROOT)/components/ble/ble_services/ble_dfu/ble_dfu_unbonded.c \
	$(SDK_ROOT)/components/ble/ble_services/ble_dis/ble_dis.c \
	$(SDK_ROOT)/components/ble/ble_services/ble_hids/ble_hids.c \
	$(SDK_ROOT)/components/ble/common/ble_advdata.c \
	$(SDK_ROOT)/components/ble/common/ble_conn_params.c \
	$(SDK_ROOT)/components/ble/common/ble_conn_state.c \
	$(SDK_ROOT)/components/ble/common/ble_srv_common.c \
	$(SDK_ROOT)/components/ble/nrf_ble_gatt/nrf_ble_gatt.c \
	$(SDK_ROOT)/components/ble/nrf_ble_qwr/nrf_ble_qwr.c \
	$(SDK_ROOT)/components/ble/peer_manager/auth_status_tracker.c \
	$(SDK_ROOT)/components/ble/peer_manager/gatt_cache_manager.c \
	$(SDK_ROOT)/components/ble/peer_manager/gatts_cache_manager.c \
	$(SDK_ROOT)/components/ble/peer_manager/id_manager.c \
	$(SDK_ROOT)/components/ble/peer_manager/peer_data_storage.c \
	$(SDK_ROOT)/components/ble/peer_manager/peer_database.c \
	$(SDK_ROOT)/components/ble/peer_manager/peer_id.c \
	$(SDK_ROOT)/components/ble/peer_manager/peer_manager.c \
	$(SDK_ROOT)/components/ble/peer_manager/peer_manager_handler.c \
	$(SDK_ROOT)/components/ble/peer_manager/pm_buffer.c \
	$(SDK_ROOT)/components/ble/peer_manager/security_dispatcher.c \
	$(SDK_ROOT)/components/ble/peer_manager/security_manager.c \
	$(SDK_ROOT)/components/libraries/atomic/nrf_atomic.c \
	$(SDK_ROOT)/components/libraries/atomic_fifo/nrf_atfifo.c \
	$(SDK_ROOT)/components/libraries/atomic_flags/nrf_atflags.c \
	$(SDK_ROOT)/components/libraries/balloc/nrf_balloc.c \
	$(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu_svci.c \
	$(SDK_ROOT)/components/libraries/crc16/crc16.c \
	$(SDK_ROOT)/components/libraries/experimental_section_vars/nrf_section_iter.c \
	$(SDK_ROOT)/components/libraries/fds/fds.c \
	$(SDK_ROOT)/components/libraries/fifo/app_fifo.c \
	$(SDK_ROOT)/components/libraries/fstorage/nrf_fstorage.c \
	$(SDK_ROOT)/components/libraries/fstorage/nrf_fstorage_sd.c \
	$(SDK_ROOT)/components/libraries/hardfault/hardfault_implementation.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_backend_rtt.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_backend_serial.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_default_backends.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_frontend.c \
	$(SDK_ROOT)/components/libraries/log/src/nrf_log_str_formatter.c \
	$(SDK_ROOT)/components/libraries/low_power_pwm/low_power_pwm.c \
	$(SDK_ROOT)/components/libraries/memobj/nrf_memobj.c \
	$(SDK_ROOT)/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c \
    $(SDK_ROOT)/components/libraries/queue/nrf_queue.c \
	$(SDK_ROOT)/components/libraries/ringbuf/nrf_ringbuf.c \
	$(SDK_ROOT)/components/libraries/scheduler/app_scheduler.c \
	$(SDK_ROOT)/components/libraries/sortlist/nrf_sortlist.c \
	$(SDK_ROOT)/components/libraries/strerror/nrf_strerror.c \
	$(SDK_ROOT)/components/libraries/timer/app_timer2.c \
	$(SDK_ROOT)/components/libraries/timer/drv_rtc.c \
	$(SDK_ROOT)/components/libraries/uart/app_uart_fifo.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd_core.c \
	$(SDK_ROOT)/components/libraries/usbd/app_usbd_string_desc.c \
	$(SDK_ROOT)/components/libraries/usbd/class/hid/app_usbd_hid.c \
	$(SDK_ROOT)/components/libraries/util/app_error.c \
	$(SDK_ROOT)/components/libraries/util/app_error_handler_gcc.c \
	$(SDK_ROOT)/components/libraries/util/app_error_weak.c \
	$(SDK_ROOT)/components/libraries/util/app_util_platform.c \
	$(SDK_ROOT)/components/libraries/util/nrf_assert.c \
	$(SDK_ROOT)/components/softdevice/common/nrf_sdh.c \
	$(SDK_ROOT)/components/softdevice/common/nrf_sdh_ble.c \
	$(SDK_ROOT)/components/softdevice/common/nrf_sdh_soc.c \
	$(SDK_ROOT)/external/fprintf/nrf_fprintf.c \
	$(SDK_ROOT)/external/fprintf/nrf_fprintf_format.c \
	$(SDK_ROOT)/external/segger_rtt/SEGGER_RTT.c \
	$(SDK_ROOT)/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c \
	$(SDK_ROOT)/external/segger_rtt/SEGGER_RTT_printf.c \
	$(SDK_ROOT)/modules/nrfx/soc/nrfx_atomic.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_clock.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/prs/nrfx_prs.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_saadc.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_wdt.c \
	$(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_uart.c


# Include folders common to all targets
INC_FOLDERS += \
	$(SDK_ROOT)/components/ble/ble_advertising \
	$(SDK_ROOT)/components/ble/ble_link_ctx_manager \
	$(SDK_ROOT)/components/ble/ble_services/ble_bas \
	$(SDK_ROOT)/components/ble/ble_services/ble_dfu \
	$(SDK_ROOT)/components/ble/ble_services/ble_dis \
	$(SDK_ROOT)/components/ble/ble_services/ble_hids \
	$(SDK_ROOT)/components/ble/common \
	$(SDK_ROOT)/components/ble/nrf_ble_gatt \
	$(SDK_ROOT)/components/ble/nrf_ble_qwr \
	$(SDK_ROOT)/components/ble/peer_manager \
	$(SDK_ROOT)/components/boards \
	$(SDK_ROOT)/components/libraries/atomic \
	$(SDK_ROOT)/components/libraries/atomic_fifo \
	$(SDK_ROOT)/components/libraries/atomic_flags \
	$(SDK_ROOT)/components/libraries/balloc \
	$(SDK_ROOT)/components/libraries/bootloader \
	$(SDK_ROOT)/components/libraries/bootloader/dfu \
	$(SDK_ROOT)/components/libraries/crc16 \
	$(SDK_ROOT)/components/libraries/delay \
	$(SDK_ROOT)/components/libraries/experimental_section_vars \
	$(SDK_ROOT)/components/libraries/fds \
	$(SDK_ROOT)/components/libraries/fifo \
	$(SDK_ROOT)/components/libraries/fstorage \
	$(SDK_ROOT)/components/libraries/hardfault \
	$(SDK_ROOT)/components/libraries/log \
	$(SDK_ROOT)/components/libraries/log/src \
	$(SDK_ROOT)/components/libraries/low_power_pwm \
	$(SDK_ROOT)/components/libraries/memobj \
	$(SDK_ROOT)/components/libraries/pwr_mgmt \
    $(SDK_ROOT)/components/libraries/queue \
	$(SDK_ROOT)/components/libraries/ringbuf \
	$(SDK_ROOT)/components/libraries/scheduler \
	$(SDK_ROOT)/components/libraries/sortlist \
	$(SDK_ROOT)/components/libraries/strerror \
	$(SDK_ROOT)/components/libraries/timer \
	$(SDK_ROOT)/components/libraries/uart \
	$(SDK_ROOT)/components/libraries/usbd \
	$(SDK_ROOT)/components/libraries/usbd/class/hid \
	$(SDK_ROOT)/components/libraries/usbd/class/hid/generic \
	$(SDK_ROOT)/components/libraries/util \
	$(SDK_ROOT)/components/softdevice/common \
	$(SDK_ROOT)/components/toolchain/cmsis/include \
	$(SDK_ROOT)/external/fprintf \
	$(SDK_ROOT)/external/segger_rtt \
	$(SDK_ROOT)/modules/nrfx \
	$(SDK_ROOT)/modules/nrfx/drivers/include \
	$(SDK_ROOT)/modules/nrfx/drivers/src \
	$(SDK_ROOT)/modules/nrfx/drivers/src/prs \
	$(SDK_ROOT)/modules/nrfx/hal \
	$(SDK_ROOT)/modules/nrfx/mdk \
	$(SDK_ROOT)/modules/nrfx/soc \
	$(SDK_ROOT)/modules/nrfx/templates \
	$(SDK_ROOT)/integration/nrfx \
	$(SDK_ROOT)/integration/nrfx/legacy


ifeq ($(NRF_DEBUG), yes)
  TMK_COMMON_DEFS += -DNRF_LOG_ENABLED=1
  TMK_COMMON_DEFS += -DNRF_LOG_BACKEND_RTT_ENABLED=1
  TMK_COMMON_DEFS += -DNRF_LOG_BACKEND_UART_ENABLED=0
  TMK_COMMON_DEFS += -DNRF_LOG_DEFAULT_LEVEL=4
else
  TMK_COMMON_DEFS += -DNRF_LOG_ENABLED=0
  TMK_COMMON_DEFS += -DNRF_LOG_BACKEND_RTT_ENABLED=0
  TMK_COMMON_DEFS += -DNRF_LOG_BACKEND_UART_ENABLED=0
  TMK_COMMON_DEFS += -DNRF_LOG_DEFAULT_LEVEL=0
endif

OPT_DEFS = $(TMK_COMMON_DEFS)

# Optimization flags
OPT = -Os -g3
# Uncomment the line below to enable link time optimization
#OPT += -flto
OPT += $(OPT_DEFS)

# C flags common to all targets
CFLAGS += $(OPT)
CFLAGS += -DNRF52_PAN_74
CFLAGS += -DNRFX_COREDEP_DELAY_US_LOOP_CYCLES=3
CFLAGS += -DAPP_TIMER_V2
CFLAGS += -DAPP_TIMER_V2_RTC1_ENABLED
CFLAGS += -DNRF_DFU_SVCI_ENABLED
CFLAGS += -DNRF_DFU_TRANSPORT_BLE=1
CFLAGS += -DNRF_SD_BLE_API_VERSION=6
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DUSE_CUSTOM_CONFIG
CFLAGS += -DPROTOCOL_NRF5
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS += -Wall -Werror
# keep every function in a separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin -fshort-enums
ifdef CONFIG_H
#    CFLAGS += -DCONFIG_H_FILE=\"$(CONFIG_H)\"
    CFLAGS += -include $(CONFIG_H)
    CFLAGS += -include $(CONFIG_H1)
endif

# C++ flags common to all targets
CXXFLAGS += $(OPT)

# Assembler flags common to all targets
ASMFLAGS += -g3
ASMFLAGS += -mcpu=cortex-m4
ASMFLAGS += -mthumb -mabi=aapcs
ASMFLAGS += -DNRF52_PAN_74
ASMFLAGS += -DNRFX_COREDEP_DELAY_US_LOOP_CYCLES=3
ASMFLAGS += -DAPP_TIMER_V2
ASMFLAGS += -DAPP_TIMER_V2_RTC1_ENABLED
ASMFLAGS += -DNRF_DFU_SVCI_ENABLED
ASMFLAGS += -DNRF_DFU_TRANSPORT_BLE=1
ASMFLAGS += -DNRF_SD_BLE_API_VERSION=6
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DUSE_CUSTOM_CONFIG
ASMFLAGS += -DPROTOCOL_NRF5
ifdef CONFIG_H
    ASFLAGS += -include $(CONFIG_H)
    ASFLAGS += -include $(CONFIG_H1)
endif


# Linker flags
LDFLAGS += $(OPT)
LDFLAGS += -mthumb -mabi=aapcs -L$(SDK_ROOT)/modules/nrfx/mdk -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m4
# let linker dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs

nrf52_kbd: CFLAGS += -D__HEAP_SIZE=$(HEAP_SIZE)
nrf52_kbd: CFLAGS += -D__STACK_SIZE=$(STACK_SIZE)
nrf52_kbd: ASMFLAGS += -D__HEAP_SIZE=$(HEAP_SIZE)
nrf52_kbd: ASMFLAGS += -D__STACK_SIZE=$(STACK_SIZE)

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIB_FILES += -lc -lnosys -lm

.PHONY: default help

# Default target - first one defined
default: nrf52_kbd

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo		nrf52_kbd
	@echo		flash_softdevice
	@echo		sdk_config 			- starting external tool for editing sdk_config.h
	@echo		flash      			- flashing binary
	@echo		setting	   			- generate dfu setting
	@echo		flash_setting		- flash dfu setting
	@echo		merge_setting		- merge dfu setting with application
	@echo		merge_softdevice	- merge softdevice with application
	@echo		merge_all 			- merge softdevice and dfu setting with application
	@echo		package	   			- pack firmware for DFU
	@echo		erase	   			- erase the chip
	@echo All targets starts with "flash" could has prefix "pyocd_", which \
	means use pyocd to flash chip. 

VERBOSE = 1
include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

.PHONY: flash setting flash_setting flash_softdevice erase pyocd_flash pyocd_flash_softdevice pyocd_erase

# Flash the program
flash: default
	@echo Flashing: $(OUTPUT_DIRECTORY)/nrf52_kbd.hex
	nrfjprog -f nrf52 --program $(OUTPUT_DIRECTORY)/nrf52_kbd.hex --sectorerase
	nrfjprog -f nrf52 --reset

pyocd_flash: default
	@echo Flashing: $(OUTPUT_DIRECTORY)/nrf52_kbd.hex
	pyocd flash -t nrf52 -e sector -f 2M $(OUTPUT_DIRECTORY)/nrf52_kbd.hex
	pyocd cmd -t nrf52 -c reset

# Generate and Flash the DFU setting
setting: default
	@echo Setting generate $(OUTPUT_DIRECTORY)/nrf52_settings.hex
	nrfutil settings generate --family $(NRF_FAMILY) --application $(OUTPUT_DIRECTORY)/nrf52_kbd.hex --application-version 1 --bootloader-version 1 --bl-settings-version 1 $(OUTPUT_DIRECTORY)/nrf52_settings.hex

flash_setting: setting
	@echo Flashing Setting: $(OUTPUT_DIRECTORY)/nrf52_settings.hex
	nrfjprog -f nrf52 --program $(OUTPUT_DIRECTORY)/nrf52_settings.hex --sectorerase
	nrfjprog -f nrf52 --reset

pyocd_flash_setting: setting
	@echo Flashing Setting: $(OUTPUT_DIRECTORY)/nrf52_settings.hex
	pyocd flash -t nrf52 -e sector -f 2M $(OUTPUT_DIRECTORY)/nrf52_settings.hex
	pyocd cmd -t nrf52 -c reset

# Package DFU firmware pack
package: default
	@echo Packing: $(OUTPUT_DIRECTORY)/nrf52_kbd.hex
	nrfutil pkg generate --hw-version 52 --application-version 1 --application $(OUTPUT_DIRECTORY)/nrf52_kbd.hex \
	--sd-req $(SOFTDEVICE_VER) --key-file $(APP_PROJ_DIR)/private.key $(NRF_PACKAGE_NAME)

# Flash softdevice
flash_softdevice:
	@echo Flashing: $(SOFTDEVICE_NAME)
	nrfjprog -f nrf52 --program $(SOFTDEVICE_PATH) --sectorerase
	nrfjprog -f nrf52 --reset

pyocd_flash_softdevice:
	@echo Flashing: $(SOFTDEVICE_NAME)
	pyocd flash -t nrf52 -e sector -f 2M $(SOFTDEVICE_PATH)
	pyocd cmd -t nrf52 -c reset

# Merge Package for download
merge_setting: setting
	@echo Merging program with signature to $(OUTPUT_DIRECTORY)/nrf52_kbd_sign.hex
	mergehex -m $(OUTPUT_DIRECTORY)/nrf52_settings.hex $(OUTPUT_DIRECTORY)/nrf52_kbd.hex -o $(OUTPUT_DIRECTORY)/nrf52_kbd_sign.hex

merge_softdevice: default
	@echo Merging program and SoftDevice $(SOFTDEVICE_NAME) to $(OUTPUT_DIRECTORY)/nrf52_kbd_with_sd.hex
	mergehex -m $(SOFTDEVICE_PATH) $(OUTPUT_DIRECTORY)/nrf52_kbd.hex -o $(OUTPUT_DIRECTORY)/nrf52_kbd_with_sd.hex

merge_all: setting
	@echo Merging program, signature and SoftDevice $(SOFTDEVICE_NAME) to $(OUTPUT_DIRECTORY)/nrf52_kbd_sign_with_sd.hex
	mergehex -m $(SOFTDEVICE_PATH) $(OUTPUT_DIRECTORY)/nrf52_settings.hex $(OUTPUT_DIRECTORY)/nrf52_kbd.hex -o $(OUTPUT_DIRECTORY)/nrf52_kbd_sign_with_sd.hex

# Erase chip
erase:
	nrfjprog -f nrf52 --eraseall

pyocd_erase:
	pyocd erase -t nrf52 -c

SDK_CONFIG_FILE := ../config/sdk_config.h
CMSIS_CONFIG_TOOL := $(SDK_ROOT)/external_tools/cmsisconfig/CMSIS_Configuration_Wizard.jar
sdk_config:
	java -jar $(CMSIS_CONFIG_TOOL) $(SDK_CONFIG_FILE)

#include $(APP_PROJ_DIR)/bl.mk
