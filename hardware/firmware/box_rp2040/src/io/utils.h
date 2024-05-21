#pragma once

#include <stdint.h>
#include <stdbool.h>

bool is_terminator(char c);
bool is_terminator_or_whitespace(char c);

void skip_whitespace(char** buf);

uint16_t parse_number(char** buf);
bool hop_word(char** ext_buf, const char* word);
