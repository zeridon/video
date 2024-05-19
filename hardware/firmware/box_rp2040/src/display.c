#include "display.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <alloca.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"
#include "config.h"

#include "mcufont.h"
#include "mf_config.h"
#include "fonts.h"
#include "io.h"

const uint16_t bg_colour = 0x2945;
const uint16_t fg_colours[] = {
    0xc924, 0x94a3, 0xd4c4, 0x4431, 0xb310, 0x6ced, 0xd2e2
};

typedef struct {
    uint16_t bg_colour;
    uint16_t fg_colour;
    enum { colour_status_unset, colour_status_set, colour_status_pending } colour_status;
    const struct mf_font_s* font;
    uint16_t* line_buf;
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
    uint16_t colour = alpha_blend(state->fg_colour, state->bg_colour, alpha);

    while (count--) {
        if (x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
            state->line_buf[y * DISPLAY_WIDTH + x] = colour;
            x++;
        }
    }
}

static uint8_t char_callback(int16_t x0, int16_t y0, mf_char character, void* v_state) {
    const uint8_t num_colours = sizeof(fg_colours) / sizeof(uint16_t);
    display_text_state_t* state = v_state;
    if (state->colour_status == colour_status_pending) {
        if (character < num_colours) {
            state->fg_colour = fg_colours[character];
            state->colour_status = colour_status_set;
        } else {
            state->colour_status = colour_status_unset;
        }
        return 0;
    }
    if (character == '\x1b') {
        state->colour_status = colour_status_pending;
        return 0;
    }
    if (state->colour_status == colour_status_unset) {
        state->fg_colour = fg_colours[(uint16_t)time_us_32() % num_colours];
    }
    return mf_render_character(state->font, x0, y0, character, &pixel_callback, state);
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

void display_init(void) {
    st7789_init(&lcd_config, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_ROTATION);

    display_fill(bg_colour);
    display_text_line(0, "Would you like them in a house?");
    display_text_line(1, "Would you like them with a mouse?");
    display_text_line(2, "");
    display_text_line(3, "I do not like them in a house.");
    display_text_line(4, "I do not like them with a mouse.");
    display_text_line(5, "I do not like them here or there.");
    display_text_line(6, "I do not like them anywhere.");
    display_text_line(7, "I do not like green eggs and ham.");
    display_text_line(8, "I do not like them, Sam-I-am.");
}

void display_fill(uint16_t colour) {
    uint16_t buf[DISPLAY_WIDTH];
    for (uint16_t i = 0; i < DISPLAY_WIDTH; i++) {
        buf[i] = colour;
    }

    st7789_set_window(0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);
    for (uint16_t i = 0; i < DISPLAY_HEIGHT; i++) {
        st7789_write(buf, sizeof(buf));
    }
}

void display_clear(void) {
    display_fill(bg_colour);
}

void display_text_line(uint8_t line_no, const char* line_text) {
    // FIXME: this approach is stupid, since we use  the font
    // height instead of line_height, which makes the line spacing too big.
    // However, there isn't a clear approach to drawing just a single line
    // without re-rendering the whole display, so maybe leave it like
    // this for now. If we do go down the re-rendering road,
    // re-rendering everything would also mean extra buffers for images,
    // keeping all the text, between renders, etc
    display_text_state_t text_state;
    text_state.font = &MF_DEFAULT_FONT;
    text_state.bg_colour = bg_colour;
    text_state.colour_status = colour_status_unset;
    uint16_t num_pixels = text_state.font->height * DISPLAY_WIDTH;
    uint16_t buf_size = num_pixels * sizeof(uint16_t);
    text_state.line_buf = alloca(buf_size);
    for (uint16_t i = 0; i < num_pixels; i++) {
        text_state.line_buf[i] = text_state.bg_colour;
    }

    mf_render_aligned(
        text_state.font,
        0, 0,
        MF_ALIGN_LEFT,
        line_text, strlen(line_text),
        &char_callback, &text_state
    );

    uint16_t x_start = 0;
    uint16_t x_end = DISPLAY_WIDTH - 1;
    uint16_t y_start = line_no * text_state.font->height;
    uint16_t y_end = y_start + text_state.font->height;

    st7789_set_window(x_start, x_end, y_start, y_end);
    st7789_write(text_state.line_buf, buf_size);
}
