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
    diff_result="$(comm -2 -3 <(topo_sort "${1}" | sort) <(extract_steps "${2}" | sort))"
    if [[ -n "${diff_result}" ]]; then
        msg "the following items are missing from ${2}:"
        for item in $(topo_sort "${1}"); do
            if grep -qFx "${item}" <<< "${diff_result}"; then
                echo "${item}"
            fi
        done
    fi

    diff_result="$(comm -1 -3 <(topo_sort "${1}" | sort) <(extract_steps "${2}" | sort))"
    if [[ -n "${diff_result}" ]]; then
        msg "the following items are missing from ${1}:"
        msg "${diff_result}"
    fi
}

topo_diff assembly.dot README.md
dot -Tsvg < assembly.dot > assembly.svg
