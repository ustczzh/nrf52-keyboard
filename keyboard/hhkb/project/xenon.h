#define XENON_GPIO_PIN_MAP(port, pin) (((port) << 5) | ((pin) & 0x1F))

#define LED_RED         XENON_GPIO_PIN_MAP(0, 13)
#define LED_GREEN       XENON_GPIO_PIN_MAP(0, 14)
#define LED_BLUE        XENON_GPIO_PIN_MAP(0, 15)

#define USB_POWER       XENON_GPIO_PIN_MAP(0, 12)
#define LI_CHARGE       XENON_GPIO_PIN_MAP(1, 9)

#define PIN_A0          XENON_GPIO_PIN_MAP(0, 3)
#define PIN_A1          XENON_GPIO_PIN_MAP(0, 4)
#define PIN_A2          XENON_GPIO_PIN_MAP(0, 28)
#define PIN_A3          XENON_GPIO_PIN_MAP(0, 29)
#define PIN_A4          XENON_GPIO_PIN_MAP(0, 30)
#define PIN_A4          XENON_GPIO_PIN_MAP(0, 30)

#define PIN_D0          XENON_GPIO_PIN_MAP(0, 26)
#define PIN_D1          XENON_GPIO_PIN_MAP(0, 27)
#define PIN_D2          XENON_GPIO_PIN_MAP(1, 1)
#define PIN_D3          XENON_GPIO_PIN_MAP(1, 2)
#define PIN_D4          XENON_GPIO_PIN_MAP(1, 8)
#define PIN_D5          XENON_GPIO_PIN_MAP(1, 10)
#define PIN_D6          XENON_GPIO_PIN_MAP(1, 11)
#define PIN_D7          XENON_GPIO_PIN_MAP(1, 12)
#define PIN_D8          XENON_GPIO_PIN_MAP(1, 3)

#define PIN_D9          XENON_GPIO_PIN_MAP(0, 6)
#define PIN_D10         XENON_GPIO_PIN_MAP(0, 8)
#define PIN_D11         XENON_GPIO_PIN_MAP(1, 14)
#define PIN_D12         XENON_GPIO_PIN_MAP(1, 13)
#define PIN_D13         XENON_GPIO_PIN_MAP(1, 15)

#define PIN_SDA         PIN_D0
#define PIN_SCL         PIN_D1

#define PIN_TX          PIN_D9
#define PIN_RX          PIN_D10
#define PIN_MISO        PIN_D11
#define PIN_MOSI        PIN_D12
#define PIN_SCK         PIN_D13
#define PIN_SS          PIN_A5

#define LED_USER        PIN_D7

// P0.24=1/P0.25=0，PCB Antenna
// P0.24=0/P0.25=1，Ext. Antenna
#define ANT_SEL1        XENON_GPIO_PIN_MAP(0, 24)
#define ANT_SEL2        XENON_GPIO_PIN_MAP(0, 25)

#define NFC1            XENON_GPIO_PIN_MAP(0, 9)
#define NFC2            XENON_GPIO_PIN_MAP(0, 10)
