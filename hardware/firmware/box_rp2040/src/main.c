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

int main(void) {
    st7789_init(&lcd_config, lcd_width, lcd_height, lcd_rotation);
    while (true) {
        sleep_ms(1000);
        st7789_fill(0xbeec);
        sleep_ms(1000);
        st7789_fill(0xdd8c);
    }
    return 0;
}
