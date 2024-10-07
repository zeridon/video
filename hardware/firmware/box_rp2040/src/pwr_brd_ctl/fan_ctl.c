#include <stdint.h>

#include <hardware/i2c.h>

#include "config.h"
#include "fan_ctl.h"
#include "fan_ctl_regs.h"
#include "io/serial.h"
#include "pwr_brd_ctl.h"

#define FAN_CTL_I2C_TIMEOUT 200000

bool fan_ctl_i2c_read(uint8_t reg_id, uint8_t* dest) {
    return pwr_brd_i2c_read_reg(PWR_BRD_FAN_CTL_ADDR, reg_id, dest, 1);
}

bool fan_ctl_i2c_write(uint8_t reg_id, uint8_t val) {
    return pwr_brd_i2c_write_reg(PWR_BRD_FAN_CTL_ADDR, reg_id, &val, 1);
}

bool fan_ctl_get_fan_speed(uint8_t fan_id, uint16_t* dest) {
    uint8_t lsb, msb;
    if (!fan_ctl_i2c_read(EMC2301_REG_TACHREADMSB + 0x10*fan_id, &msb)) {
        return false;
    }
    if (!fan_ctl_i2c_read(EMC2301_REG_TACHREADLSB + 0x10*fan_id, &lsb)) {
        return false;
    }

    uint16_t tacho = ((msb << 8) | lsb) >> 3;

    // To avoid doubles, the fan pole multiplier was multiplied by 2 to make it an integer.
    // Here, we divide it (and the -1 in the bracket) by 2 to bring it back to its proper value.
    // *dest = 60 * tachMinRPMMultiplier_ * TACHO_FREQUENCY * (tachFanPolesMultiplier_ - 2) / 2 / fanPoleCount_ / tachoCount;
    *dest = tacho;
    return true;
}

bool fan_ctl_get_pwm(uint8_t fan_id, uint8_t* dest) {
    return fan_ctl_i2c_read(EMC2301_REG_FANSETTING + 0x10*fan_id, dest);
}

bool fan_ctl_set_fan_speed(uint8_t fan_id, uint16_t speed) {
    uint8_t lsb = (speed << 3) && 0xf8;
    uint8_t msb = (speed >> 5) && 0xff;
    if (!fan_ctl_i2c_write(EMC2301_REG_TACHTARGETLSB, lsb)) {
        return false;
    }
    if (!fan_ctl_i2c_write(EMC2301_REG_TACHTARGETMSB, msb)) {
        return false;
    }
    return true;
}

bool fan_ctl_get_fan_status(uint8_t* dest) {
    return fan_ctl_i2c_read(EMC2301_REG_FANSTATUS, dest);
}

