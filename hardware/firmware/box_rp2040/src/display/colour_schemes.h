#pragma once

#include <stdint.h>

typedef uint16_t colour_t;

#define RGB_888_TO_565(col) ((colour_t)(((col >> 8) & 0xf800) | ((col >> 5) & 0x07e0) | ((col >> 3) & 0x001f)))

#ifndef _COLOUR_SCHEMES_C
extern const colour_t all_colours[];
extern const uint8_t all_colours_len;
extern const colour_t primary_colours[];
extern const uint8_t primary_colours_len;
extern const colour_t colour_bg;
extern const colour_t colour_fg;
#endif
