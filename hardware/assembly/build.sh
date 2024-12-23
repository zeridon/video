#!/bin/bash

set -euo pipefail

cd "$(dirname "$(readlink -f "${0}")")"

function msg {
    echo "${@}" >&2
}

function die {
    msg "${@}"
    exit 1
}

function topo_sort {
    cat "${1}" | grep -oE '\w+\s*->\s*\w+' | sed -E 's/\s*->\s*/ /g' | tsort || die "could not topo sort ${1}"
}

function extract_steps {
    cat "${1}" | grep -E '^`\w+`:$' | grep -oE '\w+'
}

function topo_diff {
    if ! diff_result="$(diff -u <(topo_sort "${1}") <(extract_steps "${2}"))"; then
        msg "the following items differ between ${1} and ${2}:"
        msg "${diff_result}"
    fi
}

topo_diff assembly.dot README.md
dot -Tsvg < assembly.dot > assembly.svg
