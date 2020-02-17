ifndef BOOTLOADER_DIR
  BOOTLOADER_DIR := $(ROOT_DIR)/application/bootloader/secure_bootloader/nrf52840
endif

export NRF_CHIP SOFTDEVICE NRF52_DISABLE_FPU

.PHONY: bootloader

bootloader: 
	@make -C $(BOOTLOADER_DIR) OUTPUT_DIRECTORY=$(abspath $(OUTPUT_DIRECTORY))

flash_bootloader:
	@make -C $(BOOTLOADER_DIR) OUTPUT_DIRECTORY=$(abspath $(OUTPUT_DIRECTORY)) flash

pyocd_flash_bootloader:
	@make -C $(BOOTLOADER_DIR) OUTPUT_DIRECTORY=$(abspath $(OUTPUT_DIRECTORY)) pyocd_flash
