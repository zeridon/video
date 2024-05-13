#include "io.h"

#include "usb.h"

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include <stdint.h>

#define UART_ENABLED (UART_INSTANCE != NULL)

void io_init(void) {
    if (UART_ENABLED) {
        uart_init(UART_INSTANCE, UART_BAUD);
        gpio_set_function(UART_PIN_TX, GPIO_FUNC_UART);
        gpio_set_function(UART_PIN_RX, GPIO_FUNC_UART);
    }
}

void io_say_n(char* buf, int n) {
    if (USB_ENABLED) {
        tud_cdc_write(buf, n);
    }
    if (UART_ENABLED) {
        uart_write_blocking(UART_INSTANCE, buf, n);
    }
    if (USB_ENABLED) {
        tud_cdc_write_flush();
    }
}

void io_say(char* buf) {
    io_say_n(buf, strlen(buf));
}

void io_handle_char(char chr) {
    char buf[15] = "you said: ";
    buf[10] = chr;
    buf[11] = '\r';
    buf[12] = '\n';
    buf[13] = '\0';

    if (chr == '!') {
        strcpy(buf, "bye\r\n");
        io_say(buf);
        reset_usb_boot(0, 0);
    }
    io_say(buf);
}

void io_usb_cdc_task(void) {
    if (!USB_ENABLED || !tud_cdc_connected() || !tud_cdc_available()) {
        return;
    }

    int32_t chr;
    while ( (chr = tud_cdc_read_char()) >= 0 ) {
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
