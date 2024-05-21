#include "io.h"
#include "display.h"
#include "network_switch_status_reader.h"

#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void skip_whitespace(char** buf) {
    while (**buf == ' ') {
        (*buf)++;
    }
}

uint16_t parse_number(char** buf) {
    skip_whitespace(buf);
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

bool hop_word(char** ext_buf, const char* word) {
    char* buf = *ext_buf;
    skip_whitespace(&buf);

    while (*word != 0 && !is_terminator_or_whitespace(*buf) && *buf == *word) {
        buf++;
        word++;
    }


    if (*word != '\0' || !is_terminator_or_whitespace(*buf)) {
        return false;
    }

    skip_whitespace(&buf);

    *ext_buf = buf;
    return true;
}

void help(void) {
    io_say("available commands:\n");
    io_say("    switch          -- respond with network switch info\n");
    io_say("    line            -- show text on the display (call without arguments for usage)\n");
    io_say("    clear           -- clear the display\n");
    io_say("    bootloader      -- reboot into bootloader\n");
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

    if (hop_word(&cmd_buf, "line") || hop_word(&cmd_buf, "d")) {
        if (cmd_buf[0] == '\0') {
            io_say("usage: line <line number> <line text>\n");
            io_say("line text may contain colour escape sequences\n");
            io_say("a 0x1b byte followed by a colour index (0-17) sets the colour\n");
            return;
        }
        uint16_t n = parse_number(&cmd_buf);
        display_text_line(n, cmd_buf);
        io_say("ok display line\n");
        return;
    }

    if (hop_word(&cmd_buf, "clear") || hop_word(&cmd_buf, "a")) {
        display_clear();
        io_say("ok display clear\n");
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
