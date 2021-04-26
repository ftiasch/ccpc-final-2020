#!/bin/bash
set -o nounset
set -o errexit
seed=0
while true; do
    seed=$(($seed + 1))
    if $1 $seed > input; then
        if [[ `uname -s` == "Darwin" ]]; then
            $2 < input > answer
            $3 < input > output
        else
            if ! timeout 5 $2 < input > answer; then
                >&2 echo $2 Timeout
            fi
            if ! timeout 5 $3 < input > output; then
                >&2 echo $3 Timeout
            fi
        fi
        if diff output answer >&2; then
            >&2 echo Test \#$seed OK
            head -c 128 answer | head -5 >&2
        else
            >&2 echo Test \#$seed FAILED
            echo $seed
            break
        fi
    fi
done
