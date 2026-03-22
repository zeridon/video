package ctl

type MixerState struct {
	Channels []ChannelState `json:"channels"`
	Buses    []BusState     `json:"buses"`
}

type ChannelState struct {
	Label   string      `json:"label"`
	Name    string      `json:"name"`
	Gain    float32     `json:"gain"`
	Phantom bool        `json:"phantom"`
	Sends   []SendState `json:"sends"`
}

type BusState struct {
	Label  string  `json:"label"`
	Name   string  `json:"name"`
	Volume float32 `json:"volume"`
}

type SendState struct {
	Unmuted bool    `json:"unmuted"`
	Volume  float32 `json:"volume"`
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
