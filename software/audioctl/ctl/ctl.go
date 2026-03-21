package ctl

import (
	"fmt"
	"log/slog"

	"github.com/fosdem/video/software/audioctl/config"
	"go.bug.st/serial"
)

type Ctl struct {
	cfg    *config.CtlCfg
	logger *slog.Logger
	port   serial.Port
}

func New(logger *slog.Logger, cfg *config.CtlCfg) *Ctl {
	c := &Ctl{}
	c.logger = logger
	c.cfg = cfg
	return c
}

func (c *Ctl) Loop() error {
	var err error
	mode := &serial.Mode{
		BaudRate: 115200,
	}
	c.port, err = serial.Open(c.cfg.PortDevice, mode)
	if err != nil {
		return fmt.Errorf("could not open %s: %w", c.cfg.PortDevice, err)
	}
	defer c.port.Close()

	c.logger.Info("successfully opened serial", "port", c.cfg.PortDevice)

	return fmt.Errorf("not implemented")
}
