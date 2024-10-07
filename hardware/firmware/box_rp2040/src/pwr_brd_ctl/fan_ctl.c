#include <stdint.h>

#include <hardware/i2c.h>

#include "config.h"
#include "fan_ctl.h"
#include "fan_ctl_regs.h"
#include "io/serial.h"

#define FAN_CTL_I2C_TIMEOUT 200000

bool fan_ctl_i2c_read(uint8_t reg_id, uint8_t* dest) {
    if (i2c_read_timeout_us(PWR_BRD_I2C_INST, PWR_BRD_FAN_CTL_ADDR, dest, 1, false, FAN_CTL_I2C_TIMEOUT) < 1) {
        return false;
    }
    return true;
}

bool fan_ctl_get_fan_speed(uint8_t fan_id, uint16_t* dest) {
    uint8_t b;
    if (!fan_ctl_i2c_read(EMC2301_REG_TACHREADMSB + 0x10*fan_id, &b)) {
        return false;
    }

    uint16_t tacho = b << 8;
    if (!fan_ctl_i2c_read(EMC2301_REG_TACHREADLSB + 0x10*fan_id, &b)) {
        return false;
    }
    tacho |= b;
    // tacho = tacho >> 3;

    // To avoid doubles, the fan pole multiplier was multiplied by 2 to make it an integer.
    // Here, we divide it (and the -1 in the bracket) by 2 to bring it back to its proper value.
    // fanSpeed_ = 60 * tachMinRPMMultiplier_ * TACHO_FREQUENCY * (tachFanPolesMultiplier_ - 2) / 2 / fanPoleCount_ / tachoCount;
    *dest = tacho;
}

bool fan_ctl_get_fan_status(uint8_t* dest) {
    return fan_ctl_i2c_read(EMC2301_REG_FANSTATUS, dest);
}

