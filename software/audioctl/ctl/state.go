package ctl

type MixerState struct {
	Channels []ChannelState `json:"channels"`
	Buses    []BusState     `json:"buses"`
}

type ChannelState struct {
	Name    string      `json:"name"`  // descriptive name of the input
	Label   string      `json:"label"` // short label
	Gain    float32     `json:"gain"`  // input gain in dB (0 means identity)
	Phantom bool        `json:"phantom"`
	Sends   []SendState `json:"sends"`
}

type BusState struct {
	Name   string  `json:"name"`   // descriptive name of the output bus
	Label  string  `json:"label"`  // short label
	Volume float32 `json:"volume"` // volume in dB (0 means identity)
}

type SendState struct {
	Unmuted bool    `json:"unmuted"`
	Volume  float32 `json:"volume"` // crosspoint volume in dB (0 means identity)
}

type Levels struct {
	RMS    LevelsBlock `json:"rms"`
	Peak   LevelsBlock `json:"peak"`
	Smooth LevelsBlock `json:"smooth"`
}

type LevelsBlock struct {
	Input []float32 `json:"inputs"`
	Bus   []float32 `json:"buses"`
}

func MixerStateEqual(x, y *MixerState) bool {
	if x == nil || y == nil {
		return x == y
	}

	if len(x.Channels) != len(y.Channels) ||
		len(x.Buses) != len(y.Buses) {
		return false
	}

	for i := range x.Channels {
		if !channelEqual(&x.Channels[i], &y.Channels[i]) {
			return false
		}
	}

	for i := range x.Buses {
		if !busEqual(&x.Buses[i], &y.Buses[i]) {
			return false
		}
	}

	return true
}

func channelEqual(a, b *ChannelState) bool {
	if a.Name != b.Name ||
		a.Label != b.Label ||
		a.Gain != b.Gain ||
		a.Phantom != b.Phantom ||
		len(a.Sends) != len(b.Sends) {
		return false
	}

	for i := range a.Sends {
		if !sendEqual(&a.Sends[i], &b.Sends[i]) {
			return false
		}
	}

	return true
}

func busEqual(a, b *BusState) bool {
	return a.Name == b.Name &&
		a.Label == b.Label &&
		a.Volume == b.Volume
}

func sendEqual(a, b *SendState) bool {
	return a.Unmuted == b.Unmuted &&
		a.Volume == b.Volume
}
