#pragma once

#include <stdint.h>

typedef enum {
    io_state_cmdline,
    io_state_display_img_stream,
} io_state_t;

void io_handle_cmd(char*, io_state_t*);
void io_handle_raw_byte(char, io_state_t*);
