#include "io.h"
#include "display.h"
#include "network_switch_status_reader.h"

#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint16_t parse_number(char** buf) {
    while (**buf == ' ') {
        // skip leading whitespace
        (*buf)++;
    }
    uint16_t result = 0;
    while (**buf >= '0' && **buf <= '9') {
        result *= 10;
        result += (**buf) - '0';
        (*buf)++;
    }

    if (**buf == ' ') {
        *buf++;
    }
    return result;
}

void io_handle_cmd(char* cmd_buf) {
    char print_buf[150];
    char num_buf[15];

    switch (cmd_buf[0]) {
    case 's':
        uint32_t id;
        uint32_t ver;
        ns_identify(&id, &ver);
        snprintf(print_buf, sizeof(print_buf), "network switch with id %d and ver %d\n", id, ver);
        io_say(print_buf);
        return;
    case 'd':
        if (cmd_buf[1] != ' ') {
            io_say("usage: d <line number> <line text>\n");
            io_say("line text may contain colour escape sequences\n");
            io_say("a 0x1b byte followed by a colour index (0-7) sets the colour\n");
            return;
        }
        cmd_buf += 2;
        uint16_t n = parse_number(&cmd_buf);
        display_text_line(n, cmd_buf);
        break;
    case 'a':
        display_clear();
        break;
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
