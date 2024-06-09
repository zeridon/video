#include "io/serial.h"
#include "io/utils.h"
#include "io/commands.h"

#include "usb/usb.h"
#include "config.h"

#include "pico/stdlib.h"

#include <stdint.h>

#define UART_ENABLED (UART_INSTANCE != NULL)

void io_init(void) {
    if (UART_ENABLED) {
        uart_init(UART_INSTANCE, UART_BAUD);
        gpio_set_function(UART_PIN_TX, GPIO_FUNC_UART);
        gpio_set_function(UART_PIN_RX, GPIO_FUNC_UART);
    }
}

void io_say_n(const char* buf, int n) {
    if (USB_ENABLED) {
        usb_cdc_write(buf, n);
    }
    if (UART_ENABLED) {
        uart_write_blocking(UART_INSTANCE, buf, n);
    }
}

void io_say_uint(uint32_t x) {
    char buf[10];
    int8_t i = sizeof(buf) - 1;

    buf[i] = '\0';
    for (i--; i >= 0; i--) {
        buf[i] = (x % 10) + '0';
        x /= 10;
        if (x == 0) {
            break;
        }
    }

    io_say(&buf[i]);
}

void io_say(const char* buf) {
    io_say_n(buf, strlen(buf));
}

void io_handle_char(char chr) {
    static char line_buf[100];
    static int n = 0;
    static io_state_t state = io_state_cmdline;

    if (state != io_state_cmdline) {
        io_handle_raw_byte(chr, &state);
        return;
    }

    if (n > sizeof(line_buf) - 2) {
        if (is_terminator(chr)) {
            n = 0;
            line_buf[0] = '\0';
            io_say("line too long\n");
        }
        return;
    }
    line_buf[n] = chr;
    if (!is_terminator(chr)) {
        n++;
        return;
    }
    line_buf[n] = '\0';
    n = 0;
    if (line_buf[0] == '\0') {
        return; // empty line
    }

    io_handle_cmd(line_buf, &state);
}

void io_usb_cdc_task(void) {
    int32_t chr;
    while ( (chr = usb_cdc_read_char()) >= 0 ) {
        io_handle_char((char)chr);
    }
}

void io_uart_task(void) {
    if (!UART_ENABLED) {
        return;
    }
    while (uart_is_readable(UART_INSTANCE)) {
        io_handle_char(uart_getc(UART_INSTANCE));
    }
}

void io_task(void) {
    io_usb_cdc_task();
    io_uart_task();
}
