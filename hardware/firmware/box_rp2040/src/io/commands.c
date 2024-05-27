#include "io/serial.h"
#include "io/utils.h"
#include "display/display.h"
#include "network_switch/network_switch_status_reader.h"

#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void help(void) {
    io_say("available commands:\n");
    io_say("    switch              -- respond with network switch info\n");
    io_say("    display.text.line   -- show text on the display\n");
    io_say("    display.text.clear  -- clear text shown on display\n");
    io_say("    display.refresh     -- commit all previously called display commands\n");
    io_say("    bootloader          -- reboot into bootloader\n");
    io_say("call a command without arguments for usage\n");
}

void io_handle_cmd(char* line) {
    char print_buf[150];
    char num_buf[15];

    char* cmd_buf = line;

    if (hop_word(&cmd_buf, "switch")) {
        uint32_t id;
        uint32_t ver;
        ns_identify(&id, &ver);
        snprintf(print_buf, sizeof(print_buf), "network switch with id %d and ver %d\n", id, ver);
        io_say(print_buf);
        return;
    }

    if (hop_word(&cmd_buf, "display.text.line")) {
        if (cmd_buf[0] == '\0') {
            io_say("usage: display.text.line <line number> <line text>\n");
            io_say("changes the text of the given display line\n");
            io_say("line text may contain colour escape sequences\n");
            io_say("a 0x1b byte followed by a colour index (0-17) sets the colour\n");
            return;
        }
        uint16_t n = parse_number(&cmd_buf);
        display_text_line(n, cmd_buf);
        io_say("ok display.text.line\n");
        return;
    }

    if (hop_word(&cmd_buf, "display.text.clear")) {
        display_text_clear();
        io_say("ok display.text.clear\n");
        return;
    }

    if (hop_word(&cmd_buf, "display.refresh")) {
        display_refresh();
        io_say("ok display.refresh\n");
        return;
    }

    if (hop_word(&cmd_buf, "bootloader") || hop_word(&cmd_buf, "!")) {
        io_say("\nrestarting into bootloader, bye\n");
        sleep_ms(50);
        reset_usb_boot(0, 0);
        return;
    }

    if (hop_word(&cmd_buf, "help")) {
        help();
        return;
    }


    snprintf(print_buf, sizeof(print_buf), "no such command: %s\n", cmd_buf);
    io_say(print_buf);
    io_say("say 'help' for help\n");
    return;
}
