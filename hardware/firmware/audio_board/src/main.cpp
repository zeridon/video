#include "config.h"
#include "helpers.h"
#include <stdint.h>

#include "teensyaudio.h"
#include "cli/cli.h"

#ifdef USE_EEPROM

#include "storage.h"

#endif

#ifdef USE_DISPLAY

#include "display.h"

#endif

ChanInfo channel_info[] = {
    {CHAN_WHITE, "1", "IN1", 0},      {CHAN_WHITE, "2", "IN2", 0},
    {CHAN_WHITE, "3", "IN3", 0},      {CHAN_YELLOW, "P", "PC", 0},
    {CHAN_MAGENTA, "USB", "USB1", 1}, {CHAN_MAGENTA, "USB", "USB2", 2},

    {CHAN_WHITE, "1", "OUT1", 0},     {CHAN_WHITE, "2", "OUT2", 0},
    {CHAN_GREEN, "AFL", "HP1", 1},    {CHAN_GREEN, "AFL", "HP2", 2},
    {CHAN_MAGENTA, "USB", "USB1", 1}, {CHAN_MAGENTA, "USB", "USB2", 2},
};

void setup() {
    if (CrashReport) {
        // Wait until the debug interface is ready
        while (!SerialUSB1 && millis() < 1500)
            ;
        SerialUSB1.print(CrashReport);
    }

#ifdef USE_DISPLAY
    display_setup();
#endif
    audio_load_state();

    audio_setup();

    SerialUSB.begin(115200);
    SerialUSB1.println("board ready");
}

Cli the_cli(&SerialUSB);

unsigned long last_draw = 0;
unsigned long last_save = 0;

void loop() {
    int size;

    Levels &levels = audio_get_levels();

    audio_update_levels(levels);

#ifdef USE_DISPLAY
    display_update_vu(levels.rms, channel_info);

    if (last_draw < (millis() - 16)) {
        display_update_screen();
        last_draw = millis();
    }
#endif

    the_cli.update();

#ifdef USE_EEPROM
    // save to EEPROM every 60 seconds
    if (last_save + 60000 < millis()) {
        size = audio_eeprom_save_all();
        last_save = millis();

        SerialUSB1.printf("eeprom: wrote %d bytes\n", size);
    }
#endif
}

int main() {
    setup();
    while (1) {
        loop();
    }
};
