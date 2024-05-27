#pragma once

#include <stdint.h>
#include "colour_schemes.h"

void display_init(void);
void display_refresh(void);
void display_text_line(uint8_t line_no, const char* line_text);
void display_img_fill(colour_t colour);
void display_img_clear(void);
void display_text_clear(void);
