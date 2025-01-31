#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"

#include "usb/usb.h"
#include "display/display.h"
#include "io/serial.h"
#include "pwr_brd_ctl/pwr_brd_ctl.h"
#include "network_switch/network_switch_status_reader.h"

void init(void) {
    display_init();
    usb_init();
    io_init();
    nsw_init();
    pwr_brd_ctl_init();
}

void update(void) {
    usb_task();
    io_task();
    pwr_brd_ctl_task();
}

int main(void) {
    init();
    while (true) {
        update();
    }
    return 0;
}
