package api

import "github.com/dexterlb/misirka/go/misirka"

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
