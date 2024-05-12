#include "usb.h"

// TODO: implement vendor-reset interface

void usb_init(void) {
    tud_init(BOARD_TUD_RHPORT);
}

void usb_task(void) {
    tud_task();
}
