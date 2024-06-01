#include "display.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <alloca.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"
#include "config.h"

#include "mcufont.h"
#include "fonts.h"
#include "mf_config.h"
#include "io/serial.h"
#include "display/colour_schemes.h"

colour_t img_buffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];
char text_buffer[DISPLAY_TEXT_LINES][DISPLAY_TEXT_COLS];
uint16_t text_lines_dmg;

typedef struct {
    colour_t colour_fg;
    enum { colour_status_unset, colour_status_set, colour_status_pending } colour_status;
    const struct mf_font_s* font;
    colour_t* line_buf;
} display_text_state_t;

// Fast RGB565 pixel blending
// Found in a pull request for the Adafruit framebuffer library. Clever!
// https://github.com/tricorderproject/arducordermini/pull/1/files#diff-d22a481ade4dbb4e41acc4d7c77f683d
colour_t alpha_blend(uint32_t fg, uint32_t bg, uint8_t alpha) {
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

    while (count--) {
        if (x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
            colour_t* cell = &state->line_buf[y * DISPLAY_WIDTH + x];
            *cell = alpha_blend(state->colour_fg, *cell, alpha);
            x++;
        }
    }
}

static uint8_t char_callback(int16_t x0, int16_t y0, mf_char character, void* v_state) {
    display_text_state_t* state = v_state;
    if (state->colour_status == colour_status_pending) {
        if (character < all_colours_len) {
            state->colour_fg = all_colours[character];
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
        state->colour_fg = primary_colours[(colour_t)time_us_32() % primary_colours_len];
    }
    return mf_render_character(state->font, x0, y0, character, &pixel_callback, state);
}

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
    display_img_clear();

    display_text_line(0, "Would you like them in a house?");
    display_text_line(1, "Would you like them with a mouse?");
    display_text_line(2, "");
    display_text_line(3, "I do not like them in a house.");
    display_text_line(4, "I do not like them with a mouse.");
    display_text_line(5, "I do not like them here or there.");
    display_text_line(6, "I do not like them anywhere.");
    display_text_line(7, "I do not like green eggs and ham.");
    display_text_line(8, "I do not like them, Sam-I-am.");

    display_refresh();
}

void display_full_dmg(void) {
    text_lines_dmg = 0xffff;
}

void display_img_fill(uint16_t colour) {
    for (uint16_t y = 0; y < DISPLAY_HEIGHT; y++) {
        for (uint16_t x = 0; x < DISPLAY_WIDTH; x++) {
            img_buffer[y][x] = colour;
        }
    }
    display_full_dmg();
}

void display_img_clear(void) {
    display_img_fill(colour_bg);
}

void display_text_clear(void) {
    for (uint8_t i = 0; i < DISPLAY_TEXT_LINES; i++) {
        text_buffer[i][0] = '\0';
    }
    display_full_dmg();
}

void display_text_line(uint8_t line_no, const char* line_text) {
    uint8_t i;
    for (i = 0; line_text[i] != '\0' && i < (DISPLAY_TEXT_COLS - 1); i++) {
        text_buffer[line_no][i] = line_text[i];
    }
    text_lines_dmg |= (1 << line_no);
    text_buffer[line_no][i] = '\0';
}

void display_render_line(uint8_t line_no, const char* line_text) {
    // FIXME: this approach is stupid, since we use  the font
    // height instead of line_height, which makes the line spacing too big.
    // However, there isn't a clear approach to drawing just a single line
    // without re-rendering the whole display, so maybe leave it like
    // this for now. If we do go down the re-rendering road,
    // re-rendering everything would also mean extra buffers for images,
    // keeping all the text, between renders, etc
    display_text_state_t text_state;
    text_state.font = &MF_DEFAULT_FONT;
    text_state.colour_status = colour_status_unset;
    uint16_t num_pixels = text_state.font->height * DISPLAY_WIDTH;
    uint16_t buf_size = num_pixels * sizeof(colour_t);
    text_state.line_buf = alloca(buf_size);

    uint16_t line_height = text_state.font->height;
    for (uint16_t y = 0; y < line_height; y++) {
        uint16_t global_y = line_no * line_height + y;
        for (uint16_t x = 0; x < DISPLAY_WIDTH; x++) {
            if (global_y <= DISPLAY_HEIGHT) {
                text_state.line_buf[y * DISPLAY_WIDTH + x] = img_buffer[global_y][x];
            } else {
                text_state.line_buf[y * DISPLAY_WIDTH + x] = colour_bg;
            }
        }
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

void display_refresh(void) {
    for (uint8_t i = 0; i < DISPLAY_TEXT_LINES; i++) {
        if (text_lines_dmg & (1 << i)) {
            display_render_line(i, text_buffer[i]);
        }
    }
    text_lines_dmg = 0;
}

void display_imgonly(void) {
    st7789_set_window(0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);
    st7789_write(img_buffer, sizeof(img_buffer));
    display_full_dmg();
}

struct {
    display_px_format_t px_format;
    uint16_t rect_x;
    uint16_t rect_y;
    uint16_t rect_w;
    uint16_t rect_h;
    uint16_t byte_idx;
    uint32_t rgba;
    uint8_t bytes_per_px;
    uint16_t total_bytes;
} display_img_stream_state;

void display_img_stream_begin(display_px_format_t px_format, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    display_img_stream_state.px_format = px_format;
    display_img_stream_state.rect_x = x;
    display_img_stream_state.rect_y = y;
    display_img_stream_state.rect_w = w;
    display_img_stream_state.rect_h = h;
    display_img_stream_state.byte_idx = 0;
    if (px_format == display_px_format_rgba) {
        display_img_stream_state.bytes_per_px = 4;
    } else {
        display_img_stream_state.bytes_per_px = 2;
    }
    display_img_stream_state.total_bytes = display_img_stream_state.bytes_per_px * w * h;
}

bool display_img_stream_push(char b) {
    uint16_t pixel_idx = display_img_stream_state.byte_idx / display_img_stream_state.bytes_per_px;
    uint16_t x = pixel_idx % display_img_stream_state.rect_w + display_img_stream_state.rect_x;
    uint16_t y = pixel_idx / display_img_stream_state.rect_w + display_img_stream_state.rect_y;

    switch (display_img_stream_state.px_format) {
        case display_px_format_565:
            img_buffer[y][x] <<= 8;
            img_buffer[y][x] |= b;
            break;
        case display_px_format_rgba:
            display_img_stream_state.rgba <<= 8;
            display_img_stream_state.rgba |= b;
            if (display_img_stream_state.byte_idx == 3) {
                img_buffer[y][x] = alpha_blend(
                    RGB_888_TO_565(display_img_stream_state.rgba >> 8),
                    img_buffer[y][x],
                    display_img_stream_state.rgba & 0xff
                );
            }
            break;
    }

    display_img_stream_state.byte_idx++;
    bool finished = (display_img_stream_state.byte_idx >= display_img_stream_state.total_bytes);
    if (finished) {
        display_full_dmg();
    }
    return finished;
}
