#pragma once

#include <stdint.h>
#include <stdbool.h>

void io_init(void);
void io_task(void);

void io_say_n(const char* buf, int n);
void io_say(const char* buf);
void io_say_uint(uint32_t x);
void io_say_f(const char *fmt, ...);
void io_say_bool(bool x);
