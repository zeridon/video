#define _COLOUR_SCHEMES_C
#include "colour_schemes.h"
#include "config.h"

#ifdef COLOUR_SCHEME_GRUVBOX
const colour_t all_colours[] = {
    RGB_888_TO_565(0x282828),   // bg
    RGB_888_TO_565(0xcc241d),   // red1
    RGB_888_TO_565(0x98971a),   // green1
    RGB_888_TO_565(0xd79921),   // yellow1
    RGB_888_TO_565(0x458588),   // blue1
    RGB_888_TO_565(0xb16296),   // purple1
    RGB_888_TO_565(0x689d6a),   // teal1
    RGB_888_TO_565(0xa89984),   // gray1

    RGB_888_TO_565(0x928374),   // gray2
    RGB_888_TO_565(0xfb4934),   // red2
    RGB_888_TO_565(0xb8bb26),   // green2
    RGB_888_TO_565(0xfabd2f),   // yellow2
    RGB_888_TO_565(0x83a598),   // blue2
    RGB_888_TO_565(0xd3869b),   // purple2
    RGB_888_TO_565(0x8ec07c),   // teal2
    RGB_888_TO_565(0xebdbb2),   // fg

    RGB_888_TO_565(0xd65d0e),   // orange1
    RGB_888_TO_565(0xfe8019),   // orange2
};

const colour_t primary_colours[] = {
    RGB_888_TO_565(0xfe8019),   // orange2
    RGB_888_TO_565(0xfb4934),   // red2
    RGB_888_TO_565(0xb8bb26),   // green2
    RGB_888_TO_565(0xfabd2f),   // yellow2
    RGB_888_TO_565(0x83a598),   // blue2
    RGB_888_TO_565(0xd3869b),   // purple2
    RGB_888_TO_565(0x8ec07c),   // teal2
    RGB_888_TO_565(0xebdbb2),   // fg
};

const colour_t colour_bg = all_colours[0];
const colour_t colour_fg = all_colours[15];
#endif

const uint8_t all_colours_len = (sizeof(all_colours) / sizeof(colour_t));
const uint8_t primary_colours_len = (sizeof(primary_colours) / sizeof(colour_t));
