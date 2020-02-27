
SRC_FILES += $(TMK_COMMON_DIR)/host.c \
	$(TMK_COMMON_DIR)/keyboard.c \
	$(TMK_COMMON_DIR)/matrix.c \
	$(TMK_COMMON_DIR)/action.c \
	$(TMK_COMMON_DIR)/action_tapping.c \
    $(TMK_COMMON_DIR)/action_macro.c \
	$(TMK_COMMON_DIR)/action_layer.c \
	$(TMK_COMMON_DIR)/action_util.c \
	$(TMK_COMMON_DIR)/print.c \
	$(TMK_COMMON_DIR)/debug.c \
	$(TMK_COMMON_DIR)/util.c \
	$(TMK_COMMON_DIR)/hook.c 


INC_FOLDERS += \
    $(TMK_CORE_DIR) \
    $(TMK_COMMON_DIR)

SHARED_EP_ENABLE = no
MOUSE_SHARED_EP ?= yes

# Option modules
ifeq (yes,$(strip $(UNIMAP_ENABLE)))
    SRC_FILES += $(TMK_COMMON_DIR)/unimap.c
    TMK_COMMON_DEFS += -DUNIMAP_ENABLE
    TMK_COMMON_DEFS += -DACTIONMAP_ENABLE
else
    ifeq (yes,$(strip $(ACTIONMAP_ENABLE)))
        SRC_FILES += $(TMK_COMMON_DIR)/actionmap.c
        TMK_COMMON_DEFS += -DACTIONMAP_ENABLE
    else
        SRC_FILES += $(TMK_COMMON_DIR)/keymap.c
    endif
endif

ifeq (yes,$(strip $(BOOTMAGIC_ENABLE)))
    SRC_FILES += $(TMK_COMMON_DIR)/bootmagic.c
    SRC_FILES += $(APP_SRC_DIR)/tmk/eeconfig.c
    TMK_COMMON_DEFS += -DBOOTMAGIC_ENABLE
else
    SRC_FILES += $(APP_SRC_DIR)/keyboard/keyboard_bootcheck.c
endif

ifeq (yes,$(strip $(MOUSEKEY_ENABLE)))
    SRC_FILES += $(TMK_COMMON_DIR)/mousekey.c
    TMK_COMMON_DEFS += -DMOUSEKEY_ENABLE
    TMK_COMMON_DEFS += -DMOUSE_ENABLE

    ifeq ($(strip $(MOUSE_SHARED_EP)), yes)
        TMK_COMMON_DEFS += -DMOUSE_SHARED_EP
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq (yes,$(strip $(EXTRAKEY_ENABLE)))
    TMK_COMMON_DEFS += -DEXTRAKEY_ENABLE
    SHARED_EP_ENABLE = yes
endif

ifeq (yes,$(strip $(CONSOLE_ENABLE)))
    TMK_COMMON_DEFS += -DCONSOLE_ENABLE
else
    TMK_COMMON_DEFS += -DNO_PRINT
    TMK_COMMON_DEFS += -DNO_DEBUG
endif

ifeq (yes,$(strip $(COMMAND_ENABLE)))
    SRC_FILES += $(APP_SRC_DIR)/keyboard/keyboard_command.c
    TMK_COMMON_DEFS += -DCOMMAND_ENABLE
endif

ifeq (yes,$(strip $(NKRO_ENABLE)))
    TMK_COMMON_DEFS += -DNKRO_ENABLE
    TMK_COMMON_DEFS += -DPROTOCOL_LUFA
    SHARED_EP_ENABLE = yes
endif

ifeq (yes,$(strip $(USB_6KRO_ENABLE)))
    TMK_COMMON_DEFS += -DUSB_6KRO_ENABLE
endif

ifeq (yes, $(strip $(KEYBOARD_LOCK_ENABLE)))
    TMK_COMMON_DEFS += -DKEYBOARD_LOCK_ENABLE
endif

ifeq (yes,$(strip $(BACKLIGHT_ENABLE)))
    SRC_FILES += $(TMK_COMMON_DIR)/backlight.c
    TMK_COMMON_DEFS += -DBACKLIGHT_ENABLE
endif

ifeq (yes,$(strip $(KEYMAP_SECTION_ENABLE)))
    TMK_COMMON_DEFS += -DKEYMAP_SECTION_ENABLE
endif

ifeq ($(strip $(SHARED_EP_ENABLE)), yes)
    TMK_COMMON_DEFS += -DSHARED_EP_ENABLE
endif