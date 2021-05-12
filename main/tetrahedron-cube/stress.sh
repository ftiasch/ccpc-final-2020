#!/bin/bash
set -o nounset
set -o errexit
seed=0
while true; do
    seed=$(($seed + 1))
    if ./random.exe -T 2 -m 10 $seed > input; then
        ./solution.exe < input > answer
        ./approx.exe < input > output
        if ./check_approx.exe input output answer >&2; then
            >&2 echo Test \#$seed OK
            head -c 128 answer | head -5 >&2
        else
            >&2 echo Test \#$seed FAILED
            echo $seed
            break
        fi
    fi
done
