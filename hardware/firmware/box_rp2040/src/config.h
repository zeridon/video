#pragma once

// ********** USB ***********
// set to -1 to disable USB
#define USB_INSTANCE                0
#define USB_CDC_WRITE_TIMEOUT_US    500000

// ********* UART ***********
// set to uart0, etc to enable or to NULL to disable UART
#define UART_INSTANCE               NULL
#define UART_BAUD                   115200
#define UART_PIN_TX                 0
#define UART_PIN_RX                 1

// ******** DISPLAY *********
#define DISPLAY_SPI                 spi1

#define DISPLAY_PIN_DAT             11
#define DISPLAY_PIN_CLK             10
#define DISPLAY_PIN_CS              13
#define DISPLAY_PIN_DC              19
#define DISPLAY_PIN_RST             20
#define DISPLAY_PIN_BL              22

#define DISPLAY_WIDTH               320
#define DISPLAY_HEIGHT              240
#define DISPLAY_ROTATION            ST7789_LANDSCAPE
#define DISPLAY_TEXT_COLS           42
#define DISPLAY_TEXT_LINES          10

#define COLOUR_SCHEME_GRUVBOX

// ****** NETWORK SWITCH INTERFACE *******
#define NSW_PIN_SDA                 26
#define NSW_PIN_SCL                 27
