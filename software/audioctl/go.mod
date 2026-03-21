module github.com/fosdem/video/software/audioctl

go 1.25.5

replace github.com/dexterlb/misirka/go => /home/human/s/git/misirka/go

require (
	github.com/dexterlb/misirka/go v0.0.0-00010101000000-000000000000
	github.com/goccy/go-yaml v1.19.2
	go.bug.st/serial v1.6.4
)

require (
	github.com/creack/goselect v0.1.2 // indirect
	github.com/goccy/go-json v0.10.6 // indirect
	golang.org/x/sys v0.19.0 // indirect
)
