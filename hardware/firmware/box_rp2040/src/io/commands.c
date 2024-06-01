#include "io/commands.h"
#include "config.h"
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
    io_say("    display.img         -- display an image\n");
    io_say("    display.img.clear   -- clear image(s) shown on display\n");
    io_say("    display.refresh     -- commit all previously called display commands\n");
    io_say("    display.imgonly     -- like display.refresh, but hides all text. very fast.\n");
    io_say("    bootloader          -- reboot into bootloader\n");
    io_say("call a command without arguments for usage\n");
}

void io_handle_cmd(char* line, io_state_t* state) {
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

    if (hop_word(&cmd_buf, "display.img.clear")) {
        display_img_clear();
        io_say("ok display.img.clear\n");
        return;
    }

    if (hop_word(&cmd_buf, "display.img")) {
        if (cmd_buf[0] == '\0') {
            io_say("usage: display.img (rgba|565) <x> <y> <w> <h>\n");
            io_say("displays an image inside the rectangle described by x,y,w,h\n");
            io_say("after the LF byte that terminates this command, I will listen for\n");
            io_say("a total of w*h little-endian pixels.\n");
            io_say("when the format is rgba, each pixel is 4 bytes.\n");
            io_say("when the format is 565,  each pixel is 2 bytes.\n");
            io_say("rgba allows smoothly compositing images with the background and\n");
            io_say("with each other, but is slower.\n");
            io_say("once I receive the image, I will listen for commands again.\n");
            return;
        }

        display_px_format_t px_fmt;
        if (hop_word(&cmd_buf, "rgba")) {
            px_fmt = display_px_format_rgba;
        } else if (hop_word(&cmd_buf, "565")) {
            px_fmt = display_px_format_565;
        } else {
            io_say("unknown pixel format specified\n");
            return;
        }

        uint16_t x = parse_number(&cmd_buf);
        uint16_t y = parse_number(&cmd_buf);
        uint16_t w = parse_number(&cmd_buf);
        uint16_t h = parse_number(&cmd_buf);

        if (!(x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT && w < DISPLAY_WIDTH && h < DISPLAY_HEIGHT && w > 0 && h > 0)) {
            io_say("given rectangle has a very stupid size\n");
            return;
        }

        display_img_stream_begin(px_fmt, x, y, w, h);
        *state = io_state_display_img_stream;

        return;
    }

    if (hop_word(&cmd_buf, "display.refresh")) {
        display_refresh();
        io_say("ok display.refresh\n");
        return;
    }

    if (hop_word(&cmd_buf, "display.imgonly")) {
        display_imgonly();
        io_say("ok display.imgonly\n");
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

void io_handle_raw_byte(char b, io_state_t* state) {
    switch (*state) {
        case io_state_display_img_stream:
            if (display_img_stream_push(b)) {
                *state = io_state_cmdline;
                io_say("ok display.img\n");
            }
            return;
    }
}
