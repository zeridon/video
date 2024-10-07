#pragma once

#include <stdint.h>
#include <stdbool.h>

bool fan_ctl_get_fan_speed(uint8_t fan_id, uint16_t* dest);
bool fan_ctl_get_fan_status(uint8_t* dest);
bool fan_ctl_get_pwm(uint8_t fan_id, uint8_t* dest);
bool fan_ctl_set_fan_speed(uint8_t fan_id, uint16_t speed);
