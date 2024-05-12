#include "display.h"

#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"

// lcd configuration
const struct st7789_config lcd_config = {
    .spi      = spi1,
    .gpio_din = 11,
    .gpio_clk = 10,
    .gpio_cs  = 13,
    .gpio_dc  = 19,
    .gpio_rst = 20,
    .gpio_bl  = 22,
};

const int lcd_width = 320;
const int lcd_height = 240;
const enum st7789_rotation lcd_rotation = ST7789_LANDSCAPE;

void st7789_fill(uint16_t pixel)
{
    int num_pixels = lcd_width * lcd_height;

    st7789_set_window(0, lcd_width - 1, 0, lcd_width - 1);

    uint16_t pixels[lcd_width];
    for (int i = 0; i < lcd_width; i++) {
        pixels[i] = pixel;
    }
    for (int i = 0; i < lcd_height; i++) {
        st7789_write(pixels, sizeof(pixels));
    }
}

void display_init(void) {
    st7789_init(&lcd_config, lcd_width, lcd_height, lcd_rotation);
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
