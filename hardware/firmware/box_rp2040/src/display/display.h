#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "colour_schemes.h"

typedef enum {
    display_px_format_rgba,
    display_px_format_565
} display_px_format_t;

void display_init(void);
void display_refresh(void);
void display_text_line(uint8_t line_no, const char* line_text);
void display_img_fill(colour_t colour);
void display_img_clear(void);
void display_imgonly(void);
void display_text_clear(void);
void display_img_stream_begin(display_px_format_t fmt, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
bool display_img_stream_push(char b);
