#include "display.h"

#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"
#include "config.h"

#include "mcufont.h"
#include "fonts.h"

typedef struct {
    uint16_t bg_colour;
    uint16_t fg_colour;
} display_text_state_t;

// Fast RGB565 pixel blending
// Found in a pull request for the Adafruit framebuffer library. Clever!
// https://github.com/tricorderproject/arducordermini/pull/1/files#diff-d22a481ade4dbb4e41acc4d7c77f683d
uint16_t alpha_blend(uint32_t fg, uint32_t bg, uint8_t alpha) {
    // Alpha converted from [0..255] to [0..31]
    alpha = ( alpha + 4 ) >> 3;

    // Converts  0000000000000000rrrrrggggggbbbbb
    //     into  00000gggggg00000rrrrr000000bbbbb
    // with mask 00000111111000001111100000011111
    // This is useful because it makes space for a parallel fixed-point multiply
    bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
    fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;

    // This implements the linear interpolation formula: result = bg * (1.0 - alpha) + fg * alpha
    // This can be factorized into: result = bg + (fg - bg) * alpha
    // alpha is in Q1.5 format, so 0.0 is represented by 0, and 1.0 is represented by 32
    uint32_t result = (fg - bg) * alpha; // parallel fixed-point multiply of all components
    result >>= 5;
    result += bg;
    result &= 0b00000111111000001111100000011111; // mask out fractional parts
    return (result >> 16) | result; // contract result
}

static void pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void* v_state) {
    display_text_state_t* state = v_state;
    uint16_t pixels[count];
    uint16_t colour = alpha_blend(state->fg_colour, state->bg_colour, alpha);

    for (uint8_t i = 0; i < count; i++) {
        pixels[i] = colour;
    }

    st7789_set_window(x, x + count, y, y);
    st7789_write(pixels, sizeof(pixels));
}

static uint8_t char_callback(int16_t x0, int16_t y0, mf_char character, void *state) {
    return mf_render_character(&mf_rlefont_dejavu_sans_12.font, x0, y0, character, &pixel_callback, state);
}

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

    st7789_set_window(0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);

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
    display_text_state_t text_state;
    if (now - last_switch >= 1500 * 1000) {
        if (colour == colour_a) {
            colour = colour_b;
            text_state.bg_colour = colour_b;
            text_state.fg_colour = colour_a;
        } else {
            colour = colour_a;
            text_state.bg_colour = colour_a;
            text_state.fg_colour = colour_b;
        }
        st7789_fill(colour);
        last_switch = now;

        mf_render_aligned(
            &mf_rlefont_dejavu_sans_12.font,
            0, 0,
            MF_ALIGN_LEFT,
            "Hello, World!", 13,
            &char_callback, &text_state
        );
    }
}
