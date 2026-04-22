package api

import (
	"log/slog"
	"net/http"
	"time"

	"github.com/dexterlb/misirka/go/misirka"
	"github.com/fosdem/video/software/audioctl/config"
	"github.com/fosdem/video/software/audioctl/ctl"
	"github.com/fosdem/video/software/audioctl/fakectl"
)

type Api struct {
	srv          http.Server
	m            *misirka.Misirka
	logger       *slog.Logger
	cfg          *config.ApiCfg
	ctl          ctl.Ctl
	dying        chan struct{}
	refreshState chan struct{}
	chanNames    []string
	busNames     []string
}

func New(logger *slog.Logger, cfg *config.ApiCfg, ctl ctl.Ctl) *Api {
	a := &Api{}
	a.cfg = cfg
	a.logger = logger
	a.ctl = ctl
	a.dying = make(chan struct{})
	a.refreshState = make(chan struct{})

	a.m = misirka.New(func(err error) {
		logger.Error("API error", "err", err)
	}).Descr("control API for the FOSDEM audio board")

	misirka.AddTopic(a.m, "heartbeat").
		Descr("sends a heartbeat every now and then").
		Example(Heartbeat{Now: time.Now()})

	misirka.AddTopic(a.m, "state").
		Descr("sends the full audio control state").
		Example(fakectl.DefaultState)

	misirka.AddTopic(a.m, "levels").
		Descr("sends the audio levels of all inputs and outputs, in decibels").
		Example(fakectl.DefaultLevels())

	misirka.HandleCall(a.m, "set-full-state", a.handleSetFullState).
		Descr("set the full state of the audio mixer at once").
		Example(fakectl.DefaultState, "ok")

	misirka.HandleCall(a.m, "set-matrix-send", a.handleSetMatrixSend).
		Descr("set the unmuted status of the given matrix cross-point").
		Example(exampleMatrixSendParam1, "ok").
		Example(exampleMatrixSendParam2, "ok").
		PathValueAlias("set-matrix-send/i/{channel}/{bus}/{unmuted}").
		PathValueAlias("set-matrix-send/{channel_name}/{bus_name}/{unmuted}")

	misirka.HandleCall(a.m, "set-matrix-volume", a.handleSetMatrixVolume).
		Descr("set the volume (in decibels) of the given matrix cross-point").
		Example(exampleMatrixVolumeParam1, "ok").
		Example(exampleMatrixVolumeParam2, "ok").
		PathValueAlias("set-matrix-volume/i/{channel}/{bus}/{volume}").
		PathValueAlias("set-matrix-volume/{channel_name}/{bus_name}/{volume}")

	misirka.HandleCall(a.m, "set-phantom", a.handleSetPhantom).
		Descr("turn phantom power for the given input on or off").
		Example(examplePhantomParam1, "ok").
		Example(examplePhantomParam2, "ok").
		PathValueAlias("set-phantom/i/{channel}/{phantom}").
		PathValueAlias("set-phantom/{channel_name}/{phantom}")

	misirka.HandleCall(a.m, "set-in-gain", a.handleSetInGain).
		Descr("set the input gain (in decibels) of the given input channel").
		Example(exampleInGainParam1, "ok").
		Example(exampleInGainParam2, "ok").
		PathValueAlias("set-in-gain/i/{channel}/{volume}").
		PathValueAlias("set-in-gain/{channel_name}/{volume}")

	misirka.HandleCall(a.m, "set-bus-volume", a.handleSetBusVolume).
		Descr("set the volume (in decibels) of the given output bus").
		Example(exampleBusVolumeParam1, "ok").
		Example(exampleBusVolumeParam2, "ok").
		PathValueAlias("set-bus-volume/i/{bus}/{volume}").
		PathValueAlias("set-bus-volume/{bus_name}/{volume}")

	misirka.HandleCall(a.m, "raw-cmd", a.handleRawCmd).
		Descr("execute a raw command on the audio hardware").
		Example("volume.set 0 1 2.5", "ok")

	misirka.HandleCall(a.m, "factory-reset", a.handleFactoryReset).
		Descr("factory reset the audio hardware").
		Example(FactoryResetParam{}, "ok")

	a.m.HandleDoc()
	a.m.HandleWebsocket()

	a.srv.Handler = a.m.HTTPHandler()
	a.srv.Addr = a.cfg.Bind
	return a
}

func (a *Api) Serve() error {
	defer close(a.dying)
	go a.doHeartbeat()
	go a.poller()
	a.logger.Info("starting server", "addr", a.cfg.Bind)
	return a.srv.ListenAndServe()
}

type Heartbeat struct {
	Now time.Time `json:"now"`
}

func (a *Api) doHeartbeat() {
	ticker := time.NewTicker(1 * time.Second)
	defer ticker.Stop()

	var h Heartbeat
	for {
		select {
		case <-a.dying:
			return
		case t := <-ticker.C:
			h.Now = t
			misirka.Publish(a.m, "heartbeat", h)
		}
	}
}

func (a *Api) poller() {
	pollState := time.NewTicker(time.Duration(a.cfg.StatePollIntervalMsec) * time.Millisecond)
	defer pollState.Stop()

	pollLevels := time.NewTicker(time.Duration(a.cfg.LevelsPollIntervalMsec) * time.Millisecond)
	defer pollLevels.Stop()

	a.pollState()
	for {
		select {
		case <-a.dying:
			return
		case <-a.refreshState:
			a.pollState()
		case <-pollState.C:
			a.pollState()
		case <-pollLevels.C:
			a.pollLevels()
		}
	}
}

func (a *Api) forceRefresh() {
	// TODO: throttling
	a.refreshState <- struct{}{}
}
