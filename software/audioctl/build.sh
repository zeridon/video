#!/usr/bin/env bash

set -euo pipefail

cdir="$(dirname "$(readlink -f "${0}")")"

function do_build {
    mkdir -p "${cdir}"/build
    (
        set -euo pipefail
        cd "${cdir}"
        go build -o build/audioctl 'github.com/fosdem/video/software/audioctl/cmd/audioctl'
    )
}

function reset_go_mod {
    cat > "${cdir}"/go.mod <<END
    module github.com/fosdem/video/software/audioctl

    go 1.25.5
END
    (
        set -euo pipefail
        cd "${cdir}"
        export GOPROXY=direct
        go mod tidy
    )
}

function usage {
    cat <<END
usage:
    - ${1} build
    - ${1} run <args>
    - ${1} update-deps
END
    exit 1
}

if [[ $# -eq 0 ]]; then
    usage "${0}"
fi

case "${1}" in
    build)
        do_build
        ;;
    run)
        do_build
        "${cdir}"/build/audioctl "${@:2}"
        ;;
    update-deps)
        reset_go_mod
        do_build
        ;;
    *) usage "${0}" ;;
esac
