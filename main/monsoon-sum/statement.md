---
timelimit: 1
...

# Sum

Given $n$, $x$ and $y$, let $f_{n, x, y}(a, b)$ denote the value of
$$
\sum_{i = a}^{n - b} \binom{i}{a} x^{i - a} \binom{n - i}{b} y^{n - i - b}
$$
Bobo also has $q$ pairs $(a_1, b_1), \dots, (a_q, b_q)$. Find the value of $f_{n, x, y}(a_1, b_1), \dots, f_{n, x, y}(a_q, b_q)$ **modulo** $998244353$.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains four integers $n$, $x$, $y$ and $q$.

In the following $q$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \leq n \leq 10^9$
* $0 \leq x, y < 998244353$
* $1 \leq q \leq 2 \times 10^5$
* $1 \leq a_i, b_i \leq 5000$ for each $1 \leq i \leq q$
* $a_i + b_i \leq n$ for each $1 \leq i \leq q$
* The sum of $\max(a_1, b_1, \dots, a_q, b_q)$ $\leq 5000$.
* The sum of $q$ $\leq 2 \times 10^5$.

## Output

For each pair, print an integer which denotes the value modulo $998244353$.

<!--SAMPLES-->
