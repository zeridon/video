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
}

func New(logger *slog.Logger, cfg *config.ApiCfg, ctl *ctl.Ctl) *Api {
	a := &Api{}
	a.cfg = cfg
	a.logger = logger
	a.ctl = ctl

	a.m = misirka.New("/", func(err error) {
		logger.Error("API error", "err", err)
	})

	a.m.AddTopic("heartbeat")
	misirka.HandleCall(a.m, "raw-cmd", a.handleRawCmd)

	a.srv.Handler = a.m.Handler()
	a.srv.Addr = a.cfg.Bind
	return a
}

func (a *Api) Serve() error {
	go a.doHeartbeat()
	a.logger.Info("starting server", "addr", a.cfg.Bind)
	return a.srv.ListenAndServe()
}

type Heartbeat struct {
	Now time.Time `json:"now"`
}

func (a *Api) doHeartbeat() {
	var h Heartbeat
	for {
		h.Now = time.Now()
		misirka.Publish(a.m, "heartbeat", h)
		time.Sleep(1 * time.Second)
	}
}
