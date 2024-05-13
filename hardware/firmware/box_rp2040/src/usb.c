#include "usb.h"

// TODO: implement vendor-reset interface

void usb_init(void) {
    if (!USB_ENABLED) {
        return;
    }
    tud_init(USB_INSTANCE);
}

void usb_task(void) {
    if (!USB_ENABLED) {
        return;
    }
    tud_task();
}
