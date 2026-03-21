package api

import (
	"log/slog"
	"net/http"
	"time"

	"github.com/dexterlb/misirka/go/misirka"
	"github.com/fosdem/video/software/audioctl/config"
	"github.com/fosdem/video/software/audioctl/ctl"
)

type Api struct {
	srv    http.Server
	m      *misirka.Misirka
	logger *slog.Logger
	cfg    *config.ApiCfg
	ctl    *ctl.Ctl
	dying  chan struct{}
}

func New(logger *slog.Logger, cfg *config.ApiCfg, ctl *ctl.Ctl) *Api {
	a := &Api{}
	a.cfg = cfg
	a.logger = logger
	a.ctl = ctl
	a.dying = make(chan struct{})

	a.m = misirka.New("/", func(err error) {
		logger.Error("API error", "err", err)
	})

	a.m.AddTopic("heartbeat")
	a.m.AddTopic("state")
	misirka.HandleCall(a.m, "raw-cmd", a.handleRawCmd)

	a.srv.Handler = a.m.Handler()
	a.srv.Addr = a.cfg.Bind
	return a
}

func (a *Api) Serve() error {
	defer close(a.dying)
	go a.doHeartbeat()
	go a.statePoller()
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

func (a *Api) statePoller() {
	ticker := time.NewTicker(1 * time.Second)
	defer ticker.Stop()

	for {
		select {
		case <-a.dying:
			return
		case <-ticker.C:
			state, err := a.ctl.GetFullState()
			if err != nil {
				a.logger.Error("could not poll state", "err", err)
			}
			misirka.Publish(a.m, "state", state)
		}
	}
}
