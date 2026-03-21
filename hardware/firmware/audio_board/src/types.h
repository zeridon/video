#ifndef _MIXER_TYPES_H_
#define _MIXER_TYPES_H_

#include "config.h"
#include "channels.h"
#include <stdint.h>

typedef struct {
		float matrix[CHANNELS][BUSES];

		uint64_t mutes;
		uint16_t phantoms;

		float channel_input_gains[CHANNELS];
		float bus_volumes[BUSES];
} AudioState;

typedef struct {
		float smooth[CHANNELS + BUSES];
		float peak[CHANNELS + BUSES];
		float rms[CHANNELS + BUSES];
} Levels;

#endif
