#pragma once

#include <stdbool.h>
#include <stdint.h>

void pwr_brd_ctl_init();
bool pwr_brd_raw_gpio_read(uint8_t* val);
void pwr_brd_i2c_bus_scan();
void pwr_brd_i2c_dump_all_regs(uint8_t addr);
bool temp_sensor_get_temp_raw(uint8_t* dest);
