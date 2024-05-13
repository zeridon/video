#include "display.h"

#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"
#include "config.h"

// lcd configuration
const struct st7789_config lcd_config = {
    .spi      = DISPLAY_SPI,
    .gpio_din = DISPLAY_PIN_DAT,
    .gpio_clk = DISPLAY_PIN_CLK,
    .gpio_cs  = DISPLAY_PIN_CS,
    .gpio_dc  = DISPLAY_PIN_DC,
    .gpio_rst = DISPLAY_PIN_RST,
    .gpio_bl  = DISPLAY_PIN_BL,
};

void st7789_fill(uint16_t pixel)
{
    int num_pixels = DISPLAY_WIDTH * DISPLAY_HEIGHT;

    st7789_set_window(0, DISPLAY_WIDTH - 1, 0, DISPLAY_WIDTH - 1);

    uint16_t pixels[DISPLAY_WIDTH];
    for (int i = 0; i < DISPLAY_WIDTH; i++) {
        pixels[i] = pixel;
    }
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        st7789_write(pixels, sizeof(pixels));
    }
}

void display_init(void) {
    st7789_init(&lcd_config, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_ROTATION);
}

void display_task(void) {
    static uint32_t last_switch = 0;
    uint32_t now = time_us_32();
    const uint16_t colour_a = 0xbeec;
    const uint16_t colour_b = 0xdd8c;
    static uint16_t colour;
    if (now - last_switch >= 1500 * 1000) {
        if (colour == colour_a) {
            colour = colour_b;
        } else {
            colour = colour_a;
        }
        st7789_fill(colour);
        last_switch = now;
    }
}
