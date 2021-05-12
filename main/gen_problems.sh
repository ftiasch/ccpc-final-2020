#!/bin/bash
for sol in $(wc -w */solution.cc | head -n -1 | sort -g -k 1 | awk '{split($0, a, " ");print a[2]}'); do
  dirname ${sol}
done > PROBLEMS
