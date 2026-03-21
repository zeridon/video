package config

import "fmt"

type ApiCfg struct {
	Bind string
}

func (a *ApiCfg) Validate() error {
	if a.Bind == "" {
		return fmt.Errorf("`bind` should be nonempty")
	}
	return nil
}
