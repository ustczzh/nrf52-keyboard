#include "config.h"

#if defined(PROTOCOL_NRF5)
#   define KEYBOARD_REPORT_BITS (NKRO_EPSIZE - 1)
#endif