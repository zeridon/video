#include "pwr_brd_ctl.h"
#include "config.h"
#include "io/serial.h"
#include "rp2040_tca9534.h"
#include <pico/stdlib.h>
#include <hardware/i2c.h>

TCA9534 expander;

void pwr_brd_ctl_init() {
    // gpio_init(PWR_BRD_I2C_SDA);
    // gpio_init(PWR_BRD_I2C_SCL);
    i2c_init(PWR_BRD_I2C_INST, PWR_BRD_I2C_BAUD);
    gpio_pull_up(PWR_BRD_I2C_SDA);
    gpio_pull_up(PWR_BRD_I2C_SCL);
    gpio_set_function(PWR_BRD_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PWR_BRD_I2C_SCL, GPIO_FUNC_I2C);
    expander = tca9534_Init(TCA9534_ADDR, PWR_BRD_I2C_INST);
}

bool pwr_brd_raw_gpio_read(uint8_t* val) {
    bool result = tca9534_ReadRegister(&expander, InputPort);
    if (result) {
        *val = expander.input_reg;
    }
    return result;
}

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

bool temp_sensor_get_temp_raw(uint8_t* dest) {
    return (i2c_read_blocking_until(PWR_BRD_I2C_INST, PWR_BRD_TEMP_SENS_ADDR, dest, 1, false, make_timeout_time_ms(20)) >= 0);
}

void pwr_brd_i2c_bus_scan() {
    io_say("begin pb.i2c.scan:\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking_until(PWR_BRD_I2C_INST, addr, &rxdata, 1, false, make_timeout_time_ms(20));

        if (ret >= 0) {
            io_say("found device at ");
            io_say_uint(addr);
            io_say("\n");
        }
    }
    io_say("ok pb.i2c.scan\n");
}

void pwr_brd_i2c_dump_all_regs(uint8_t addr) {
    io_say("begin pb.i2c.dump_all_regs:\n");

    for (uint8_t reg = 0x0; reg < 0xfe; reg++) {
        uint8_t val = 0;
        io_say("reg ");
        io_say_uint(reg);
        io_say(": ");
        if (i2c_read_timeout_us(PWR_BRD_I2C_INST, addr, &val, 1, false, 200000) < 1) {
            io_say_uint(val);
        } else {
            io_say("fail");
        }
        io_say("\n");
    }
    io_say("ok pb.i2c.dump_all_regs\n");
}
