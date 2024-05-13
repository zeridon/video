#include "io.h"
#include "network_switch_status_reader.h"

#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_terminator(char c) {
    return c == '\n' || c == '\r' || c == '\0';
}

void io_handle_char(char chr) {
    static char in_buf[100];
    char print_buf[150];
    static int n = 0;

    if (n > sizeof(in_buf) - 2) {
        if (is_terminator(chr)) {
            io_say("line too long\n");
        }
        return;
    }
    in_buf[n++] = chr;
    if (!is_terminator(chr)) {
        return;
    }
    in_buf[n] = '\0';
    n = 0;
    if (in_buf[0] == '\0') {
        return; // empty line
    }

    snprintf(print_buf, sizeof(print_buf), "you said: %s\n", in_buf);
    io_say(print_buf);

    switch (in_buf[0]) {
    case 's':
        uint32_t id;
        uint32_t ver;
        ns_identify(&id, &ver);
        snprintf(print_buf, sizeof(print_buf), "network switch with id %d and ver %d\n", id, ver);
        io_say(print_buf);
        return;
    case '!':
        io_say("\nrestarting into bootloader, bye\n");
        sleep_ms(50);
        reset_usb_boot(0, 0);
        return;
    }
}
