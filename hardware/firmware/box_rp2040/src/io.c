#include "io.h"

#include "usb.h"

#include "pico/stdlib.h"

#include <stdint.h>

void io_init(void) {

}

void io_task(void) {
    if (!tud_cdc_connected() || !tud_cdc_available()) {
        return;
    }

    static uint32_t last_print = 0;
    uint32_t now = time_us_32();
    if (now - last_print >= 1500 * 1000) {
        tud_cdc_write_char('b');
        tud_cdc_write_flush();
        last_print = now;
    }
}
