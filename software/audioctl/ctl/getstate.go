package ctl

import (
	"fmt"
	"strconv"
	"strings"
)

type MixerState struct {
	Channels []ChannelState `json:"channels"`
	Buses    []BusState     `json:"buses"`
}

type ChannelState struct {
	Label   string      `json:"label "`
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

func (c *Ctl) GetFullState() (*MixerState, error) {
	chanNames, busNames, err := c.GetChannelNames()
	if err != nil {
		return nil, fmt.Errorf("could not get channel names: %w", err)
	}
	chanLabels, busLabels, err := c.GetChannelLabels()
	if err != nil {
		return nil, fmt.Errorf("could not get channel labels: %w", err)
	}

	gains, err := c.GetInputGains()
	if err != nil {
		return nil, fmt.Errorf("could not get input gains: %w", err)
	}

	busVolumes, err := c.GetBusVolumes()
	if err != nil {
		return nil, fmt.Errorf("could not get bus volumes: %w", err)
	}

	phantoms, err := c.GetPhantoms()
	if err != nil {
		return nil, fmt.Errorf("could not get phantoms: %w", err)
	}

	sends, err := c.GetMatrix()
	if err != nil {
		return nil, fmt.Errorf("could not get matrix: %w", err)
	}

	numChans := len(chanNames)
	numBuses := len(busNames)
	if len(chanLabels) != numChans || len(busLabels) != numBuses {
		return nil, fmt.Errorf("item length mismatch (channel.labels and channel.names returned mismatching data)")
	}

	m := &MixerState{
		Channels: make([]ChannelState, numChans),
		Buses:    make([]BusState, numBuses),
	}

	for i := range m.Channels {
		m.Channels[i].Label = chanLabels[i]
		m.Channels[i].Name = chanNames[i]
		m.Channels[i].Gain = gains[i]
		m.Channels[i].Phantom = phantoms[i]
		m.Channels[i].Sends = make([]SendState, numBuses)
		for j := range m.Buses {
			m.Channels[i].Sends[j] = sends[i*numBuses+j]
		}
	}

	for j := range m.Buses {
		m.Buses[j].Label = busLabels[j]
		m.Buses[j].Name = busNames[j]
		m.Buses[j].Volume = busVolumes[j]
	}

	return m, nil
}

func (c *Ctl) GetChannelNames() ([]string, []string, error) {
	resp, err := c.RawCmd("channel.names")
	if err != nil {
		return nil, nil, err
	}
	return parseChannelBusList(resp, "channels", "buses")
}

func (c *Ctl) GetChannelLabels() ([]string, []string, error) {
	resp, err := c.RawCmd("channel.labels")
	if err != nil {
		return nil, nil, err
	}
	return parseChannelBusList(resp, "channels", "buses")
}

func (c *Ctl) GetInputGains() ([]float32, error) {
	resp, err := c.RawCmd("gains")
	if err != nil {
		return nil, err
	}
	return parseFloatList(resp)
}

func (c *Ctl) GetBusVolumes() ([]float32, error) {
	resp, err := c.RawCmd("bus-volumes")
	if err != nil {
		return nil, err
	}
	return parseFloatList(resp)
}

func (c *Ctl) GetPhantoms() ([]bool, error) {
	resp, err := c.RawCmd("phantoms")
	if err != nil {
		return nil, err
	}
	return parseBoolList(resp)
}

func (c *Ctl) GetMatrix() ([]SendState, error) {
	resp, err := c.RawCmd("matrix")
	if err != nil {
		return nil, err
	}

	fields := strings.Fields(resp)
	result := make([]SendState, len(fields))
	for i, f := range fields {
		result[i], err = parseSend(f)
		if err != nil {
			return nil, err
		}
	}

	return result, nil
}

func parseSend(s string) (SendState, error) {
	var ss SendState
	var err error

	fields := strings.Split(s, "*")
	if len(fields) != 2 {
		return ss, fmt.Errorf("%s is not in the form <send>*<volume>", s)
	}

	if fields[0] == "0" {
		ss.Unmuted = false
	} else if fields[0] == "1" {
		ss.Unmuted = true
	} else {
		return ss, fmt.Errorf("%s is not a valid mute/unmute value (0|1)", fields[0])
	}

	vol, err := strconv.ParseFloat(fields[1], 32)
	if err != nil {
		return ss, fmt.Errorf("invalid float (%s): %w", fields[1], err)
	}
	ss.Volume = float32(vol)

	return ss, nil
}

func parseBoolList(s string) ([]bool, error) {
	fields := strings.Fields(s)
	result := make([]bool, len(fields))
	for i, f := range fields {
		if f == "0" {
			result[i] = false
		} else if f == "1" {
			result[i] = true
		} else {
			return nil, fmt.Errorf("%s is not a bool", f)
		}
	}
	return result, nil
}

func parseFloatList(s string) ([]float32, error) {
	fields := strings.Fields(s)
	result := make([]float32, len(fields))
	for i, f := range fields {
		v, err := strconv.ParseFloat(f, 32)
		if err != nil {
			return nil, fmt.Errorf("invalid float at index %d: %w", i, err)
		}
		result[i] = float32(v)
	}
	return result, nil
}

func parseChannelBusList(resp, channelKey, busKey string) ([]string, []string, error) {
	// Expected structure: "<channelKey>: ...; <busKey>: ..."
	parts := strings.SplitN(resp, ";", 2)
	if len(parts) != 2 {
		return nil, nil, fmt.Errorf("expected two semicolon-separated sections, got %q", resp)
	}

	parseSection := func(s, key string) ([]string, error) {
		s = strings.TrimSpace(s)
		prefix := key + ":"
		if !strings.HasPrefix(s, prefix) {
			return nil, fmt.Errorf("expected section to start with %q, got %q", prefix, s)
		}
		s = strings.TrimPrefix(s, prefix)
		s = strings.TrimSpace(s)
		if s == "" {
			return []string{}, nil
		}
		return strings.Fields(s), nil
	}

	channels, err := parseSection(parts[0], channelKey)
	if err != nil {
		return nil, nil, err
	}
	buses, err := parseSection(parts[1], busKey)
	if err != nil {
		return nil, nil, err
	}

	return channels, buses, nil
}
