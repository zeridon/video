package ctl

import "fmt"

func (c *Ctl) SetMatrixSend(ch uint8, bus uint8, unmuted bool) error {
	if int(ch) >= c.numChans || int(bus) > c.numBuses {
		return fmt.Errorf("malformed input")
	}

	_, err := c.RawCmd(fmt.Sprintf("send.set %d %d %d", ch, bus, boolToNum(unmuted)))
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

func (c *Ctl) SetInGain(ch uint8, gain float32) error {
	if int(ch) >= c.numChans {
		return fmt.Errorf("malformed input")
	}

	_, err := c.RawCmd(fmt.Sprintf("in-gain.set %d %.4f", ch, gain))
	if err != nil {
		return err
	}

	return nil
}

func (c *Ctl) SetPhantom(ch uint8, phantom bool) error {
	if int(ch) >= c.numChans {
		return fmt.Errorf("malformed input")
	}

	_, err := c.RawCmd(fmt.Sprintf("phantom.set %d %d", ch, boolToNum(phantom)))
	if err != nil {
		return err
	}

	return nil
}

func (c *Ctl) SetBusVolume(bus uint8, volume float32) error {
	if int(bus) > c.numBuses {
		return fmt.Errorf("malformed input")
	}

	_, err := c.RawCmd(fmt.Sprintf("bus-volume.set %d %.4f", bus, volume))
	if err != nil {
		return err
	}

	return nil
}

func boolToNum(b bool) int {
	if b {
		return 1
	} else {
		return 0
	}
}
