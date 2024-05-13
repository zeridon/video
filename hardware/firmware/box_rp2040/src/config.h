#pragma once

// set to -1 to disable USB
#define USB_INSTANCE     0

#define DISPLAY_SPI      spi1

#define DISPLAY_PIN_DAT  11
#define DISPLAY_PIN_CLK  10
#define DISPLAY_PIN_CS   13
#define DISPLAY_PIN_DC   19
#define DISPLAY_PIN_RST  20
#define DISPLAY_PIN_BL   22

#define DISPLAY_WIDTH    320
#define DISPLAY_HEIGHT   240
#define DISPLAY_ROTATION ST7789_LANDSCAPE
