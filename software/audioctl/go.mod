module github.com/fosdem/video/software/audioctl

go 1.25.5

replace github.com/dexterlb/misirka/go => /home/human/s/git/misirka/go

require (
	github.com/dexterlb/misirka/go v0.0.0-00010101000000-000000000000
	github.com/goccy/go-yaml v1.19.2
)

require github.com/goccy/go-json v0.10.6 // indirect
