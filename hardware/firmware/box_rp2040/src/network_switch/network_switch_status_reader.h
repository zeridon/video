#pragma once

#include <stdbool.h>
#include <stdint.h>

void nsw_init(void);
bool nsw_identify(uint32_t* id, uint32_t* ver);
void nsw_read_and_print(void);
