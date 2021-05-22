---
timelimit: 1
...

# Cipher

Given three arrays $f$, $g$, $h$ of length $2^m$, Bobo defines $\mathrm{enc}(x, y) = (a, b)$ where

* $a = y \oplus g[x \oplus f[y]]$
* $b = x \oplus f[y] \oplus h[y \oplus g[x \oplus f[y]]]$.

He also has $q$ questions $(a_1, b_1), \dots, (a_q, b_q)$.

For each $(a_i, b_i)$, find a pair $(x, y)$ where $0 \leq x, y < 2^m$ and $\mathrm{enc}(x, y) = (a_i, b_i)$. It is guaranteed that for each $(a_i, b_i)$, there exists a **unique** pair $(x, y)$ satisfying the condition.

*Note*: $\oplus$ denotes the bitwise exclusive-or, i.e., xor.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains two integers $m$ and $q$.

The second line contains $2^m$ integers $f[0], \dots, f[2^m - 1]$.

The third line contains $2^m$ integers $g[0], \dots, g[2^m - 1]$.

The forth line contains $2^m$ integers $h[0], \dots, h[2^m - 1]$.

For the following $q$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \le m \leq 16$
* $1 \leq q \leq 10^5$
* $0 \leq f[i], g[i], h[i] < 2^m$ for each $0 \leq i < 2^m$
* $0 \leq a_i, b_i < 2^m$ for each $1 \leq i \leq q$
* The sum of $2^m$ $\leq 10^5$
* The sum of $q$ $\leq 10^5$

## Output

For each question, output two integers which denote the found $x$ and $y$.

<!--SAMPLES-->
