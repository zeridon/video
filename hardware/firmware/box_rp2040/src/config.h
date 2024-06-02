#pragma once

// ********** USB ***********
// set to -1 to disable USB
#define USB_INSTANCE                0
#define USB_CDC_WRITE_TIMEOUT_US    500000
#define USB_MAGIC_BAUD_RESTART_BL   134

// ********* UART ***********
// set to uart0, etc to enable or to NULL to disable UART
#define UART_INSTANCE               NULL
#define UART_BAUD                   115200
#define UART_PIN_TX                 0
#define UART_PIN_RX                 1

// ******** DISPLAY *********
#define DISPLAY_SPI                 spi1

// note: the radxa pin header silkscreen text is flipped
// (the silkscreen next to pin1 says "40")
// the radxa pins in the following comments follow the actual
// pin numbers and not the silkscreen ones
// 3v3 pins are coloured yellow (or was it red?)
// and gnd pins are coloured black (colours are correct)
#define DISPLAY_PIN_DAT             11  // radxa pin 10 (next to 3v3)
#define DISPLAY_PIN_CLK             10  // radxa pin 12 (next to gnd)
#define DISPLAY_PIN_CS              13  // radxa pin 17
#define DISPLAY_PIN_DC              19  // radxa pin 25 (between two gnd's)
#define DISPLAY_PIN_RST             20  // radxa pin 37 (next to gnd)
#define DISPLAY_PIN_BL              22  // radxa pin 33 (next to gnd), not present on all displays

#define DISPLAY_WIDTH               320
#define DISPLAY_HEIGHT              240
#define DISPLAY_ROTATION            ST7789_LANDSCAPE
#define DISPLAY_TEXT_COLS           42
#define DISPLAY_TEXT_LINES          10

#define COLOUR_SCHEME_GRUVBOX

// ****** NETWORK SWITCH INTERFACE *******
#define NSW_PIN_SDA                 26
#define NSW_PIN_SCL                 27
