#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"

// lcd configuration
const struct st7789_config lcd_config = {
    .spi      = spi1,
    .gpio_din = 12,
    .gpio_clk = 10,
    .gpio_cs  = 13,
    .gpio_dc  = 19,
    .gpio_rst = 20,
    .gpio_bl  = 22,
};

const int lcd_width = 320;
const int lcd_height = 240;

void st7789_fill(uint16_t pixel)
{
    int num_pixels = lcd_width * lcd_height;

    st7789_set_window(0, 0, lcd_width, lcd_height);

    for (int i = 0; i < num_pixels; i++) {
        st7789_write(&pixel, sizeof(pixel));
    }
}

int main(void) {
    st7789_init(&lcd_config, lcd_width, lcd_height, ST7789_LANDSCAPE);
    while (true) {
        sleep_ms(200);
        st7789_fill(0x0000);
        sleep_ms(200);
        st7789_fill(0xffff);
    }
    return 0;
}
