#include "io.h"

#include "usb.h"

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include <stdint.h>

void io_init(void) {

}

void io_handle_char(char chr) {
    char buf[15] = "you said: ";
    buf[11] = chr;
    buf[12] = '\r';
    buf[13] = '\n';
    buf[14] = '\0';
    tud_cdc_write(buf, 14);
    tud_cdc_write_flush();
    if (chr == '!') {
        strcpy(buf, "bye\r\n");
        tud_cdc_write(buf, 5);
        tud_cdc_write_flush();
        reset_usb_boot(0, 0);
    }
}

void io_usb_cdc_task() {
    if (!USB_ENABLED || !tud_cdc_connected() || !tud_cdc_available()) {
        return;
    }

    int32_t chr;
    while ( (chr = tud_cdc_read_char()) >= 0 ) {
        io_handle_char((char)chr);
    }
}

void io_task(void) {
    io_usb_cdc_task();
}

