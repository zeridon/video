package fakectl

import "github.com/fosdem/video/software/audioctl/ctl"

var defaultState *ctl.MixerState = &ctl.MixerState{
	Channels: []ctl.ChannelState{
		{
			Name:    "fubalina",
			Label:   "foo",
			Gain:    3,
			Phantom: false,
			Sends: []ctl.SendState{
				{
					Unmuted: true,
					Volume:  1,
				},
				{
					Unmuted: false,
					Volume:  1,
				},
			},
		},
		{
			Name:    "barabela",
			Label:   "bar",
			Gain:    8,
			Phantom: false,
			Sends: []ctl.SendState{
				{
					Unmuted: false,
					Volume:  1,
				},
				{
					Unmuted: true,
					Volume:  0.42,
				},
			},
		},
		{
			Name:    "bazinga",
			Label:   "baz",
			Gain:    42,
			Phantom: true,
			Sends: []ctl.SendState{
				{
					Unmuted: false,
					Volume:  1,
				},
				{
					Unmuted: true,
					Volume:  0.82,
				},
			},
		},
	},
	Buses: []ctl.BusState{
		{
			Name:   "penka",
			Label:  "pe",
			Volume: 0.4,
		},
		{
			Name:   "donka",
			Label:  "do",
			Volume: 0.4,
		},
	},
}
