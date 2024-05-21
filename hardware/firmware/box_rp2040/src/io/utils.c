#include "utils.h"

bool is_terminator(char c) {
    return c == '\n' || c == '\r' || c == '\0';
}

bool is_terminator_or_whitespace(char c) {
    return is_terminator(c) || c == ' ' || c == '\t';
}

void skip_whitespace(char** buf) {
    while (**buf == ' ') {
        (*buf)++;
    }
}

uint16_t parse_number(char** buf) {
    skip_whitespace(buf);
    uint16_t result = 0;
    while (**buf >= '0' && **buf <= '9') {
        result *= 10;
        result += (**buf) - '0';
        (*buf)++;
    }

    if (**buf == ' ') {
        *buf++;
    }
    return result;
}

bool hop_word(char** ext_buf, const char* word) {
    char* buf = *ext_buf;
    skip_whitespace(&buf);

    while (*word != 0 && !is_terminator_or_whitespace(*buf) && *buf == *word) {
        buf++;
        word++;
    }


    if (*word != '\0' || !is_terminator_or_whitespace(*buf)) {
        return false;
    }

    skip_whitespace(&buf);

    *ext_buf = buf;
    return true;
}
