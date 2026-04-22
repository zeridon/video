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
