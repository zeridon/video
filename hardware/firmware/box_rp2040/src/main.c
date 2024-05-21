#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"

#include "usb/usb.h"
#include "display/display.h"
#include "io/serial.h"
#include "network_switch/network_switch_status_reader.h"

void init(void) {
    display_init();
    usb_init();
    io_init();
    ns_init();
}

void update(void) {
    usb_task();
    io_task();
}

int main(void) {
    init();
    while (true) {
        update();
    }
    return 0;
}
