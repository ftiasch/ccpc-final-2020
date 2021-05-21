---
timelimit: 1
...

# Cipher

Bobo has three arrays $f$, $g$, $h$ of length $2^m$. Let $\mathrm{enc}(x, y) = (x'', y'')$ where

* $x'' = y \oplus g[x \oplus f[y]]$
* $y'' = x \oplus f[y] \oplus h[y \oplus g[x \oplus f[y]]]$.

($\oplus$ denotes the bitwise exclusive-or (xor))

Bobo also has $q$ questions $(a_1, b_1), \dots, (a_q, b_q)$. For each $(a_i, b_i)$, find all the pairs $(x, y)$ where $0 \leq x, y < 2^m$ and $\mathrm{enc}(x, y) = (a_i, b_i)$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $q$.

The second line contains $2^m$ integers $f[0], \dots, f[2^m - 1]$.

The third line contains $2^m$ integers $g[0], \dots, g[2^m - 1]$.

The forth line contains $2^m$ integers $h[0], \dots, h[2^m - 1]$.

For the following $q$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \le m \leq 16$
* $1 \leq q \leq 2 \times 10^5$
* $0 \leq f[i], g[i], h[i] < 2^m$ for each $0 \leq i < 2^m$
* $0 \leq a_i, b_i < 2^m$ for each $1 \leq i \leq q$

## Output

For each question, output an integer $k$, which denotes the number of pairs $(x, y)$, followed by $k$ pairs $(x_1, y_1), \dots, (x_k, y_k)$.

<!--SAMPLES-->
