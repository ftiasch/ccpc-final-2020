---
timelimit: 1
...

# Permutation Pattern

A sequence $a_1, \dots, a_m$ of $m$ distinct numbers is called *without 231* if there is **no** triples $(i, j, k)$ where $1 \leq i < j < k \leq m$ and $a_k < a_i < a_j$.

Bobo has a permutation $p_1, \dots, p_n$ of $1, \dots, n$, and he can remove some (possibly none, but not all) elements from the permutation. Find the number of sequences without $231$ among $(2^n - 1)$ resulting permutations.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains an integer $n$.

The second line contains $n$ integers $p_1, \dots, p_n$.

* $1 \leq n \leq 50$
* $1 \leq p_i \leq n$ for each $1 \leq i \leq n$
* In each input, the sum of $n$ does not exceed $50$.

## Output

For each test case, output an integer which denotes the number of sequences.

<!--SAMPLES-->
