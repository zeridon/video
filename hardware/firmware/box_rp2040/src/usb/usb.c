#include "usb.h"
#include "config.h"
#include "pico/bootrom.h"

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

bool usb_cdc_connected(void) {
    return USB_ENABLED && tud_cdc_connected();
}

void usb_cdc_write(const char *buf, int length) {
    // this is an almost-copy-paste from the pi pico stdio implementation
    static uint64_t last_avail_time;
    if (usb_cdc_connected()) {
        for (int i = 0; i < length;) {
            int n = length - i;
            int avail = (int) tud_cdc_write_available();
            if (n > avail) n = avail;
            if (n) {
                int n2 = (int) tud_cdc_write(buf + i, (uint32_t)n);
                tud_task();
                tud_cdc_write_flush();
                i += n2;
                last_avail_time = time_us_64();
            } else {
                tud_task();
                tud_cdc_write_flush();
                if (!usb_cdc_connected() ||
                    (!tud_cdc_write_available() && time_us_64() > last_avail_time + USB_CDC_WRITE_TIMEOUT_US)) {
                    break;
                }
            }
        }
    } else {
        // reset our timeout
        last_avail_time = 0;
    }
}

int32_t usb_cdc_read(char* buf, uint32_t size) {
    if (!usb_cdc_connected()) {
        return -1;
    }

    return tud_cdc_read(buf, size);
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_coding_cb(uint8_t itf, cdc_line_coding_t const* p_line_coding) {
    uint32_t baud = p_line_coding->bit_rate;
    if (baud == USB_MAGIC_BAUD_RESTART_BL) {
        // when baud is set to the magic number, restart into bootloader
        reset_usb_boot(0, 0);
    }
}
