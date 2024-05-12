#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"

#include "usb.h"
#include "display.h"
#include "io.h"

void init(void) {
    display_init();
    usb_init();
    io_init();
}

void update(void) {
    display_task();
    io_task();
    usb_task();
}

int main(void) {
    init();
    while (true) {
        update();
    }
    return 0;
}
