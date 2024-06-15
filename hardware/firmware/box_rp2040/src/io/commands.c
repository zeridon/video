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

void help(void) {
    io_say("available commands:\n");
    io_say("    netswitch.info      -- respond with network switch info\n");
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
    if (hop_word(&line, "netswitch.info")) {
        uint32_t id;
        uint32_t ver;
        if (nsw_identify(&id, &ver)) {
            io_say("begin netswitch.info (id: ");
            io_say_uint(id);
            io_say(", ver: ");
            io_say_uint(ver);
            io_say(")\n");

            nsw_port_regs_t port_regs;
            for (uint8_t port = 0; port < NSW_NUM_PORTS; port++) {
                io_say("port ");
                io_say_uint(port);
                io_say(": ");
                if (!nsw_read_port_regs(port, &port_regs)) {
                    io_say("unknown (failure getting port info)\n");
                    continue;
                }

                bool link_up = false;
                switch (nsw_link_state(&port_regs)) {
                    case nsw_link_unknown:
                        io_say("unknown");
                        break;
                    case nsw_link_down:
                        io_say("down");
                        break;
                    case nsw_link_full_duplex:
                        io_say("up full-duplex");
                        link_up = true;
                        break;
                    case nsw_link_half_duplex:
                        io_say("up half-duplex");
                        link_up = true;
                        break;
                }
                if (link_up) {
                    io_say(" ");
                    io_say_uint(nsw_link_speed_mbps(&port_regs));
                    io_say("mbps");
                }
                io_say("\n");
            }

            io_say("end netswitch.info\n");
        } else {
            io_say("fail netswitch.info\n");
            return;
        }
        return;
    }

    if (hop_word(&line, "display.text.line")) {
        if (line[0] == '\0') {
            io_say("usage: display.text.line <line number> <line text>\n");
            io_say("changes the text of the given display line\n");
            io_say("line text may contain colour escape sequences\n");
            io_say("a 0x1b byte followed by a colour index (0-17) sets the colour\n");
            return;
        }
        uint16_t n = parse_number(&line);
        display_text_line(n, line);
        io_say("ok display.text.line\n");
        return;
    }

    if (hop_word(&line, "display.text.clear")) {
        display_text_clear();
        io_say("ok display.text.clear\n");
        return;
    }

    if (hop_word(&line, "display.img.clear")) {
        display_img_clear();
        io_say("ok display.img.clear\n");
        return;
    }

    if (hop_word(&line, "display.img")) {
        if (line[0] == '\0') {
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
        if (hop_word(&line, "rgba")) {
            px_fmt = display_px_format_rgba;
        } else if (hop_word(&line, "565")) {
            px_fmt = display_px_format_565;
        } else {
            io_say("unknown pixel format specified\n");
            return;
        }

        uint16_t x = parse_number(&line);
        uint16_t y = parse_number(&line);
        uint16_t w = parse_number(&line);
        uint16_t h = parse_number(&line);

        if (!(x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT && w <= DISPLAY_WIDTH && h <= DISPLAY_HEIGHT && w > 0 && h > 0)) {
            io_say("given rectangle has a very stupid size\n");
            return;
        }

        display_img_stream_begin(px_fmt, x, y, w, h);
        *state = io_state_display_img_stream;

        return;
    }

    if (hop_word(&line, "display.refresh")) {
        display_refresh();
        io_say("ok display.refresh\n");
        return;
    }

    if (hop_word(&line, "display.imgonly")) {
        display_imgonly();
        io_say("ok display.imgonly\n");
        return;
    }

    if (hop_word(&line, "bootloader") || hop_word(&line, "!")) {
        io_say("\nrestarting into bootloader, bye\n");
        sleep_ms(50);
        reset_usb_boot(0, 0);
        return;
    }

    if (hop_word(&line, "help")) {
        help();
        return;
    }


    io_say("no such command: ");
    io_say(line);
    io_say("\nsay 'help' for help\n");
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
