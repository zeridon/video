#pragma once

#include <stdint.h>

void display_init(void);
void display_text_line(uint8_t line_no, const char* line_text);
void display_fill(uint16_t colour);
void display_clear(void);
