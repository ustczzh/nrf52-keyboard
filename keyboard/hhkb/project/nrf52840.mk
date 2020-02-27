SRC_FILES += \
  $(SDK_ROOT)/modules/nrfx/mdk/gcc_startup_nrf52840.S \
  $(SDK_ROOT)/modules/nrfx/mdk/system_nrf52840.c \

CFLAGS += -DBOARD_PCA10056
CFLAGS += -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DNRF52840_XXAA

ASMFLAGS += -DBOARD_PCA10056
ASMFLAGS += -DCONFIG_GPIO_AS_PINRESET
ASMFLAGS += -DNRF52840_XXAA

ifndef NRF52_DISABLE_FPU
  CFLAGS += -DFLOAT_ABI_HARD
  CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  ASMFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  ASMFLAGS += -DFLOAT_ABI_HARD
  LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Libraries common to all targets
LIB_FILES += \
  $(SDK_ROOT)/external/nrf_oberon/lib/cortex-m4/hard-float/liboberon_3.0.1.a \
  $(SDK_ROOT)/external/nrf_cc310_bl/lib/cortex-m4/hard-float/libnrf_cc310_bl_0.9.12.a \

else

  CFLAGS += -DFLOAT_ABI_SOFT
  CFLAGS += -mfloat-abi=soft
  ASMFLAGS += -mfloat-abi=soft
  ASMFLAGS += -DFLOAT_ABI_SOFT

# Libraries common to all targets
  LIB_FILES += \
    $(SDK_ROOT)/external/nrf_oberon/lib/cortex-m4/soft-float/liboberon_3.0.1.a \
    $(SDK_ROOT)/external/nrf_cc310_bl/lib/cortex-m4/soft-float/libnrf_cc310_bl_0.9.12.a \

endif

CFLAGS += -DS140
ASMFLAGS += -DS140
SOFTDEVICE_NAME := s140_nrf52_7.0.1_softdevice.hex
SOFTDEVICE_VER  := 0xb7
SOFTDEVICE_PATH := $(SDK_ROOT)/components/softdevice/s140/hex/s140_nrf52_7.0.1_softdevice.hex

INC_FOLDERS += \
  $(SDK_ROOT)/components/softdevice/s140/headers/nrf52 \
  $(SDK_ROOT)/components/softdevice/s140/headers

SOFTDEVICE := S140
HEAP_SIZE := 8192
STACK_SIZE := 8192

LD_NAME := nrf52840_s140.ld

NRF_FAMILY := NRF52
