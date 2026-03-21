package ctl

import "fmt"

func (c *Ctl) SetMatrixSend(ch uint8, bus uint8, unmuted bool) error {
	if int(ch) >= c.numChans || int(bus) > c.numBuses {
		return fmt.Errorf("malformed input")
	}

	_, err := c.RawCmd(fmt.Sprintf("send.set %d %d %d", ch, bus, unmuted))
	if err != nil {
		return err
	}

	return nil
}

func (c *Ctl) SetMatrixVolume(ch uint8, bus uint8, volume float32) error {
	if int(ch) >= c.numChans || int(bus) > c.numBuses {
		return fmt.Errorf("malformed input")
	}

	_, err := c.RawCmd(fmt.Sprintf("volume.set %d %d %.4f", ch, bus, volume))
	if err != nil {
		return err
	}

	return nil
}
