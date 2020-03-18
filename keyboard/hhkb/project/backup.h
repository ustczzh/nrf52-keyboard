

// 键盘配置存储（FDS）
//#define SAVE_KEYMAP /* 启用keymap存储 */
//#define SAVE_UNIMAP /* 启用unimap存储 */
//#define SAVE_MACRO  /* 启用宏存储功能 */
//#define SAVE_CONFIG /* 启用配置存储功能 */

// 键盘额外功能
//#define DYNAMIC_TX_POWER /* 启用自动发射功率调整 */
//#define HIGH_TX_POWER /* 更改发射功率到+4dBm */
//#define PASSKEY_REQUIRED /* 需要输入配对码 */
//#define ENABLE_WATCHDOG /* 启用看门狗 */
//#define MULTI_DEVICE_SWITCH  /*启用多设备切换 */
// #define MACRO_BLOCKING_MODE /* 在宏播放时禁用其他按键输入 */
// #define DEBUG_SKIP_PWRON_CHECK /*  直接开机而跳过开机条件检测，用于调试 */


/* TMK固件内置功能 */
/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

// /* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
// /* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

// LED 配置
// #define HAS_LED 0
// #define LED_NUM 22
// #define LED_CAPS 21
// #define LED_SCLK 23
// #define LED_POSITIVE // LED上拉驱动


// USB UART 传输配置
// #define HAS_USB // 启用与CH554的通信支持
// #define HAS_USBD_NRF  // 启用nRF52840的usbd
// #define HAS_USB_HOST // 启用与MAX3421e的通信支持

// #define UART_RXD 17 // UART_RX口IO
// #define UART_TXD 18 // UART_TX口IO
// #define UART_DET 19 // UART 检测引脚，若此脚被拉低，则说明USB正在工作。若不配置则使用RX口作为检测引脚
// #define UART_BAUDRATE NRF_UART_BAUDRATE_115200 // 通信波特率，请不要修改

/* define if matrix has ghost */
// #define MATRIX_HAS_GHOST /* 按键阵列是否出现Ghost Key，若没有加二极管则需要启用这个项目 */

//#define DEBOUNCE 5 /* 硬件消抖次数，设置为0则不消抖 */
//#define MATRIX_SCAN_DELAY_CYCLE 36 /* 按键扫描等待IO稳定的延时时长 */

// #define RGB_MATRIX_KEYPRESSES
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_LED_PROCESS_LIMIT 20
// #define RGB_MATRIX_LED_FLUSH_LIMIT 26
// #define DRIVER_ADDR_1 0b1010000
// #define DRIVER_ADDR_2 0b1010000

// #define DRIVER_COUNT 1
// #define DRIVER_1_LED_TOTAL 48
// #define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

// #define DISABLE_RGB_MATRIX_ALPHAS_MODS
// #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #define DISABLE_RGB_MATRIX_BREATHING
// #define DISABLE_RGB_MATRIX_BAND_SAT
// #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #define DISABLE_RGB_MATRIX_RAINDROPS
// #define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
// #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #define DISABLE_RGB_MATRIX_SPLASH
// #define DISABLE_RGB_MATRIX_SOLID_SPLASH

// The pin number for SCL pin
//#define I2C1_SCL 15
// The pin number for SDA pin
//#define I2C1_SDA 17