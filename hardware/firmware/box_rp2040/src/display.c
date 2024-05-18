#include "display.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"
#include "config.h"

#include "mcufont.h"
#include "mf_config.h"
#include "fonts.h"
#include "io.h"

const uint16_t colours[] = {
    0xc924, 0x94a3, 0xd4c4, 0x4431, 0xb310, 0x6ced, 0xd2e2
};

typedef struct {
    uint16_t bg_colour;
    uint16_t fg_colour;
    uint8_t fg_colour_idx;
    const struct mf_font_s* font;
} display_text_state_t;

uint16_t framebuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];

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
            framebuffer[y][x] = colour;
            x++;
        }
    }
}

static uint8_t char_callback(int16_t x0, int16_t y0, mf_char character, void* v_state) {
    display_text_state_t* state = v_state;
    state->fg_colour_idx = (state->fg_colour_idx + 1) % (sizeof(colours) / sizeof(uint16_t));
    state->fg_colour = colours[state->fg_colour_idx];
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

void fill_whole_buf(uint16_t colour) {
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            framebuffer[y][x] = colour;
        }
    }
}

void update_display() {
    st7789_set_window(0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);

    st7789_write(framebuffer, sizeof(framebuffer));
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
    text_state.font = &MF_DEFAULT_FONT;
    text_state.bg_colour = 0x2945;
    static uint8_t i = 0;
    text_state.fg_colour_idx = i;
    i = (i + 1) % (sizeof(colours) / sizeof(uint16_t));
    char sbuf[100];
    static const char text[128][128] = {
        "He took his vorpal sword",
        "    in hand;",
        "Long time the manxome foe",
        "    he sought",
        "So rested he by the Tumtum tree",
        "And stood awhile in thought.",
        "And, as in uffish thought",
            "he stood,",
        "",
        "The Jabberwock,",
        "   with eyes of flame",
    };
    if (now - last_switch >= 100 * 1000) {
        last_switch = now;
        uint32_t t_render = time_us_32();
        fill_whole_buf(text_state.bg_colour);

        for (uint8_t j = 0; j < sizeof(text) / sizeof(text[0]); j++) {
            mf_render_aligned(
                text_state.font,
                0, 18 * j,
                MF_ALIGN_LEFT,
                text[j], strlen(text[j]),
                &char_callback, &text_state
            );
        }
        t_render = time_us_32() - t_render;
        uint32_t t_update = time_us_32();
        update_display();
        t_update = time_us_32() - t_update;

        snprintf(sbuf, sizeof(sbuf), "t_render: %dus, t_update: %dus\n", t_render, t_update);
        io_say(sbuf);
    }
}
