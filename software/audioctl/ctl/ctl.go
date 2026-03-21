package ctl

import (
	"bufio"
	"fmt"
	"log/slog"
	"strings"
	"time"

	"github.com/fosdem/video/software/audioctl/config"
	"go.bug.st/serial"
)

type Ctl struct {
	cfg    *config.CtlCfg
	logger *slog.Logger
	port   serial.Port

	slug uint16

	reqs      chan *requestSync
	input     chan string
	readerErr chan error
}

func New(logger *slog.Logger, cfg *config.CtlCfg) *Ctl {
	c := &Ctl{}
	c.logger = logger
	c.cfg = cfg
	c.input = make(chan string)
	c.readerErr = make(chan error)
	c.reqs = make(chan *requestSync)
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

	go c.reader()

	for {
		select {
		case err := <-c.readerErr:
			return fmt.Errorf("could not read from port: %w", err)
		case data := <-c.input:
			c.handleUnsolicitedInput(data)
		case req := <-c.reqs:
			<-req.Finish
		}
	}
}

func (c *Ctl) RawCmd(argstr string) (string, error) {
	req := newReq()
	defer close(req.Finish)
	c.reqs <- req

	c.slug += 1
	if c.slug == 0 {
		c.slug = 1
	}

	fmt.Fprintf(c.port, "%d %s\n", c.slug, argstr)

	timeout := time.After(1 * time.Second)

	for {
		select {
		case data := <-c.input:
			if resp, ok := c.parseResponse(data); ok {
				return resp, nil
			}
			c.handleUnsolicitedInput(data)
		case <-timeout:
			return "", fmt.Errorf("request to hardware timed out")
		}
	}
}

// requestSync is used to serialise requests
type requestSync struct {
	Finish chan struct{}
}

func newReq() *requestSync {
	return &requestSync{
		Finish: make(chan struct{}),
	}
}

func (c *Ctl) parseResponse(data string) (string, bool) {
	return "not implemented", true
}

func (c *Ctl) handleUnsolicitedInput(data string) {
	if msg, ok := strings.CutPrefix(data, "[log] "); ok {
		c.logger.Info("log", "msg", msg)
		return
	}
	c.logger.Error("unsolicited data received", "data", data)
}

func (c *Ctl) reader() {
	scanner := bufio.NewScanner(c.port)
	for scanner.Scan() {
		c.input <- scanner.Text()
	}
	err := scanner.Err()
	if err == nil {
		err = fmt.Errorf("port was probably closed")
	}
	c.readerErr <- err
}
