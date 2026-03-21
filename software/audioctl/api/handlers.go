package api

import (
	"fmt"

	"github.com/dexterlb/misirka/go/misirka"
)

func (a *Api) handleRawCmd(param string) (string, *misirka.MErr) {
	resp, err := a.ctl.RawCmd(param)
	if err != nil {
		return "", &misirka.MErr{
			Code: -42,
			Err:  err,
		}
	}
	return resp, nil
}

type SetMatrixVolumeParam struct {
	Chan     *uint8   `json:"channel"`
	Bus      *uint8   `json:"bus"`
	ChanName *string  `json:"channel_name"`
	BusName  *string  `json:"bus_name"`
	Volume   *float32 `json:"volume"`
}

func (a *Api) handleSetMatrixVolume(param SetMatrixVolumeParam) (string, *misirka.MErr) {
	err := a.getChanByName(&param.Chan, param.ChanName)
	if err != nil {
		return "", &misirka.MErr{
			Code: -1000,
			Err:  err,
		}
	}
	err = a.getBusByName(&param.Bus, param.BusName)
	if err != nil {
		return "", &misirka.MErr{
			Code: -1000,
			Err:  err,
		}
	}

	if param.Chan == nil || param.Bus == nil || param.Volume == nil {
		return "", &misirka.MErr{
			Code: -1000,
			Err:  fmt.Errorf("missing fields (need channel, bus, unmuted)"),
		}
	}
	err = a.ctl.SetMatrixVolume(*param.Chan, *param.Bus, *param.Volume)
	if err != nil {
		return "", &misirka.MErr{
			Code: -42,
			Err:  err,
		}
	}
	a.forceRefresh()
	return "ok", nil
}

type SetMatrixSendParam struct {
	Chan     *uint8  `json:"channel"`
	Bus      *uint8  `json:"bus"`
	ChanName *string `json:"channel_name"`
	BusName  *string `json:"bus_name"`
	Unmuted  *bool   `json:"unmuted"`
}

func (a *Api) handleSetMatrixSend(param SetMatrixSendParam) (string, *misirka.MErr) {
	err := a.getChanByName(&param.Chan, param.ChanName)
	if err != nil {
		return "", &misirka.MErr{
			Code: -1000,
			Err:  err,
		}
	}
	err = a.getBusByName(&param.Bus, param.BusName)
	if err != nil {
		return "", &misirka.MErr{
			Code: -1000,
			Err:  err,
		}
	}

	if param.Chan == nil || param.Bus == nil || param.Unmuted == nil {
		return "", &misirka.MErr{
			Code: -1000,
			Err:  fmt.Errorf("missing fields (need channel, bus, unmuted)"),
		}
	}
	err = a.ctl.SetMatrixSend(*param.Chan, *param.Bus, *param.Unmuted)
	if err != nil {
		return "", &misirka.MErr{
			Code: -42,
			Err:  err,
		}
	}
	a.forceRefresh()
	return "ok", nil
}

func (a *Api) pollState() {
	state, err := a.ctl.GetFullState()
	if err != nil {
		a.logger.Error("could not poll state", "err", err)
	}
	misirka.Publish(a.m, "state", state)
}

func (a *Api) pollLevels() {
	levels, err := a.ctl.GetLevels()
	if err != nil {
		a.logger.Error("could not poll levels", "err", err)
	}
	misirka.Publish(a.m, "levels", levels)
}

func (a *Api) getChanByName(idx **uint8, name *string) error {
	if name == nil {
		return nil
	}
	for i := range a.ctl.ChanNames {
		if *name == a.ctl.ChanNames[i] {
			j := uint8(i)
			*idx = &j
			return nil
		}
	}

	return fmt.Errorf("no such chan: %s", *name)
}

func (a *Api) getBusByName(idx **uint8, name *string) error {
	if name == nil {
		return nil
	}
	for i := range a.ctl.BusNames {
		if *name == a.ctl.BusNames[i] {
			j := uint8(i)
			*idx = &j
			return nil
		}
	}

	return fmt.Errorf("no such bus: %s", *name)
}
