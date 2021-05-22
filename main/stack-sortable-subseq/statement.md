---
timelimit: 1
...

# Without 231

A sequence $a_1, \dots, a_m$ of distinct numbers is *without 231* if there is no triples $(i, j, k)$ where $1 \leq i < j < k \leq m$ and $a_k < a_i < a_j$.

Bobo has a permutation $p_1, \dots, p_n$ of $1, \dots, n$, and he can remove some (possibly none, but not all) elements from the permutation. Find out the number of sequences without $231$ among $(2^n - 1)$ resulting permutations.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains an integer $n$.

The second line contains $n$ integers $p_1, \dots, p_n$.

* $1 \leq n \leq 50$
* $1 \leq p_i \leq n$ for each $1 \leq i \leq n$
* The sum of $n$ $\leq 50$

## Output

For each test cases, output an integer which denotes the number of sequences.

<!--SAMPLES-->
