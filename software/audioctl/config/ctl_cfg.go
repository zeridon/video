package config

import "fmt"

type CtlCfg struct {
	PortDevice string `yaml:"port_device"`
}

func (a *CtlCfg) Validate() error {
	if a.PortDevice == "" {
		return fmt.Errorf("`port_device` should be nonempty")
	}
	return nil
}
