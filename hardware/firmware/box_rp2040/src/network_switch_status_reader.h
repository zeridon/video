#pragma once

#include <stdbool.h>
#include <stdint.h>

void ns_init(void);
void ns_identify(uint32_t* id, uint32_t* ver);
void ns_read_and_print(void);
