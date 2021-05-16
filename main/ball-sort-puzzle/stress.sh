#!/bin/bash
set -o nounset
set -o errexit
seed=0
while true; do
    seed=$(($seed + 1))
    if $1 $seed > input; then
        if ! timeout 5 ./very_slow.exe < input > answer; then
            >&2 echo very_slow Timeout
        fi
        if ! timeout 5 ./solution.exe < input > output; then
            >&2 echo solution Timeout
        fi
        if ./check.exe input output answer >&2; then
            >&2 echo Test \#$seed OK
            head -c 128 answer | head -5 >&2
        else
            >&2 echo Test \#$seed FAILED
            echo $seed
            break
        fi
    fi
done
