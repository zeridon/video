#include <Audio.h>
#include <Wire.h>

#include "config.h"

#include "teensyaudio.h"

#ifdef USE_EEPROM

#include "storage.h"
#define STATE_EEPROM_OFFSET 0x0

#endif

#include "taa3040.h"
#include "teensyaudio_defaults.cpp"
#include "teensyaudio_generated.cpp"

AudioControlTAA3040 taa3040;

AudioMixer4 *matrix[6][2] = {
    {&mixer1, &mixer2}, {&mixer4, &mixer5}, {&mixer7, &mixer8},
    {&mixer10, &mixer11}, {&mixer13, &mixer14}, {&mixer16, &mixer17},
};

AudioAnalyzeRMS *ent_rms[12] = {
    &rms1, &rms2, &rms3, &rms4, &rms5, &rms6,
    &rms7, &rms8, &rms9, &rms10, &rms11, &rms12,
};

AudioAnalyzePeak *ent_peak[12] = {
    &peak1, &peak2, &peak3, &peak4, &peak5, &peak6,
    &peak7, &peak8, &peak9, &peak10, &peak11, &peak12,
};

Levels levels;
AudioState state;

void audio_setup() {
    AudioMemory(80);

    Wire.begin();
    Wire1.begin();

    pinMode(PIN_PHANTOM_IN1, OUTPUT);
    pinMode(PIN_PHANTOM_IN2, OUTPUT);
    pinMode(PIN_PHANTOM_IN3, OUTPUT);

    taa3040.enable();
}

void audio_update_levels(Levels &levels) {
    float temp;
    if (rms1.available()) {
        for (uint8_t i = 0; i < CHANNELS + BUSES; i++) {
            temp = ent_rms[i]->read();
            levels.smooth[i] = ((levels.smooth[i] * 9) + temp) / 10;
            temp = levels.smooth[i];
            // VU meter drains slowly after a peak
            if (temp < levels.rms[i]) {
                levels.rms[i] *= 0.97;
            } else {
                levels.rms[i] = temp;
            }
            levels.peak[i] = ent_peak[i]->read();
        }

        taa3040.getAsiStatus();
    }
}

Levels &audio_get_levels() { return levels; }

void raw_set_crosspoint(uint8_t channel, uint8_t bus, float volume) {
    matrix[bus][channel / 4]->gain(channel % 4, volume);
}

float raw_get_crosspoint(uint8_t channel, uint8_t bus) {
    return matrix[bus][channel / 4]->getGain(channel % 4);
}

uint64_t mute_mask(uint64_t channel, uint64_t bus) {
    return (uint64_t)1 << (uint64_t)((channel * CHANNELS) + bus);
}

void apply_phantom(uint8_t channel) {
    bool is_on = (state.phantoms & (1 << channel)) > 0;
    switch (channel) {
        case 0:
            digitalWrite(PIN_PHANTOM_IN1, is_on);
            break;
        case 1:
            digitalWrite(PIN_PHANTOM_IN2, is_on);
            break;
        case 2:
            digitalWrite(PIN_PHANTOM_IN3, is_on);
            break;
    }
}

bool is_phantom_on(uint8_t channel) {
    return !!(state.phantoms & (1 << channel));
}

void set_phantom_on(uint8_t channel) {
    if (channel > 2) {
        return;
    }
    state.phantoms |= (1 << channel);
    apply_phantom(channel);
}

void set_phantom_off(uint8_t channel) {
    if (channel > 2) {
        return;
    }
    state.phantoms &= ~(1 << channel);
    apply_phantom(channel);
}

bool is_muted(uint8_t channel, uint8_t bus) {
    return !!(state.mutes & mute_mask(channel, bus));
}

float calc_real_volume(uint8_t channel, uint8_t bus, float volume) {
    return volume * !is_muted(channel, bus) * state.bus_volumes[bus];
}

void apply_volume(uint8_t channel, uint8_t bus) {
    float volume = state.matrix[channel][bus];
    raw_set_crosspoint(channel, bus, calc_real_volume(channel, bus, volume));
}

void set_volume(uint8_t channel, uint8_t bus, float volume) {
    state.matrix[channel][bus] = volume;
    apply_volume(channel, bus);
}

float get_volume(uint8_t channel, uint8_t bus) { return state.matrix[channel][bus]; }

void mute(uint8_t channel, uint8_t bus) {
    state.mutes |= mute_mask(channel, bus);
    apply_volume(channel, bus);
}

void unmute(uint8_t channel, uint8_t bus) {
    state.mutes &= ~mute_mask(channel, bus);
    apply_volume(channel, bus);
}

void set_bus_volume(uint8_t bus, float vol) {
    state.bus_volumes[bus] = vol;
    for (uint8_t channel = 0; channel < CHANNELS; ++channel) {
        apply_volume(channel, bus);
    }
}

float get_bus_volume(uint8_t bus) { return state.bus_volumes[bus]; }

void set_channel_input_gain_db(uint8_t channel, float gain) {
    uint8_t whole_gain = (uint8_t)(gain + 0.5);
    if (gain < 1) {
        whole_gain = 1;
    }
    if (gain > 42) {
        whole_gain = 42;
    }

    state.channel_input_gains[channel] = (float)whole_gain;
    taa3040.gain(channel, whole_gain, IMPEDANCE_10k, 0, 0);
}

void apply_channel_input_gain(uint8_t channel) {
    set_channel_input_gain_db(channel, state.channel_input_gains[channel]);
}

float get_channel_input_gain_db(uint8_t channel) {
    return state.channel_input_gains[channel];
}

void reset_matrix() { memcpy(state.matrix, default_matrix, sizeof(state.matrix)); }

void reset_mutes() {
    memcpy(&state.mutes, &default_mutes, sizeof(state.mutes));
}

void reset_phantoms() {
    memcpy(&state.phantoms, &default_phantoms, sizeof(state.phantoms));
}

void reset_bus_volumes() {
    memcpy(state.bus_volumes, default_bus_volumes,
           BUSES * sizeof(float));
}

void reset_channel_input_gains() {
    memcpy(state.channel_input_gains, default_channel_input_gains_db,
           CHANNELS * sizeof(float));
}

void apply_all() {
    uint8_t i, j;
    for (i = 0; i < CHANNELS; ++i) {
        apply_channel_input_gain(i);
        apply_phantom(i);
        for (j = 0; j < BUSES; ++j) {
            apply_volume(i, j);
        }
    }
}

void audio_reset_default_state() {
    reset_matrix();
    reset_mutes();
    reset_phantoms();
    reset_bus_volumes();
    reset_channel_input_gains();
}

bool matrix_ok() {
    uint8_t i, j;
    for (i = 0; i < CHANNELS; ++i) {
        for (j = 0; j < BUSES; ++j) {
            if (isnan(state.matrix[i][j])) {
                return false;
            }
        }
    }

    return true;
}

bool bus_volumes_ok() {
    uint8_t i;
    for (i = 0; i < BUSES; ++i) {
        if (isnan(state.bus_volumes[i])) {
            return false;
        }
    }

    return true;
}

bool channel_input_gains_ok() {
    uint8_t i;
    for (i = 0; i < CHANNELS; ++i) {
        if (isnan(state.channel_input_gains[i])) {
            return false;
        }
    }

    return true;
}

#ifdef USE_EEPROM
uint8_t audio_eeprom_save_all() {
    return eeprom_save_all(state, STATE_EEPROM_OFFSET);
}
#endif

void audio_load_state() {
#ifdef USE_EEPROM
    eeprom_load_all(state, STATE_EEPROM_OFFSET);

    if (!matrix_ok() || !bus_volumes_ok() || !channel_input_gains_ok()) {
        audio_reset_default_state();
        audio_eeprom_save_all();
    }

#else
    audio_reset_default_state();
#endif
    apply_all();
}
