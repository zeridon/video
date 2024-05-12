#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/st7789.h"

void init(void) {
    display_init();
}

void update(void) {
    display_task();
}

int main(void) {
    init();
    while (true) {
        update();
    }
    return 0;
}
