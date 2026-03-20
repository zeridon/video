#ifndef _TEENSY_AUDIO_H_
#define _TEENSY_AUDIO_H_

#include "config.h"

#include "types.h"

#include <stdbool.h>

void audio_setup();
void audio_load_state();

void update_levels(float levels_smooth[CHANNELS + BUSES],
                   float levels_rms[CHANNELS + BUSES],
                   float levels_peak[CHANNELS + BUSES]);

bool is_muted(uint8_t channel, uint8_t bus);
void mute(uint8_t channel, uint8_t bus);
void unmute(uint8_t channel, uint8_t bus);

void set_volume(uint8_t channel, uint8_t bus, float gain);
float get_volume(uint8_t channel, uint8_t bus);

float get_bus_multiplier(uint8_t bus);
void set_bus_multiplier(uint8_t bus, float multiplier);

float get_channel_multiplier(uint8_t channel);
void set_channel_multiplier(uint8_t channel, float multiplier);

// void raw_set_crosspoint(uint8_t channel, uint8_t bus, float gain);
float raw_get_crosspoint(uint8_t channel, uint8_t bus);

void audio_update_levels(Levels &levels);
Levels &audio_get_levels();

void audio_reset_default_state();

#ifdef USE_EEPROM
uint8_t audio_eeprom_save_all();
#endif

#endif
