#include "io.h"
#include "network_switch_status_reader.h"

#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void io_handle_cmd(const char* cmd_buf) {
    char print_buf[150];

    switch (cmd_buf[0]) {
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
    default:
        snprintf(print_buf, sizeof(print_buf), "no such command: %s\n", cmd_buf);
        io_say(print_buf);
        return;
    }
}
