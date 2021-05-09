# Sum

Given $n$ and $x$, let $f_{n, x}(a, b)$ denote the value of 
$$
\sum_{i = a}^{n - b} \binom{i}{a} x^{i - a} \binom{n - i}{b} (x + 1)^{n - i - b}
$$
Bobo also has $q$ pairs $(a_1, b_1), \dots, (a_q, b_q)$. Find the value of $f_{n, x}(a_1, b_1), \dots, f_{n, x}(a_q, b_q)$ modulo $998244353$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains three integers $n$, $x$ and $q$.

In the following $q$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \leq n \leq 10^9$
* $0 \leq n \leq 10^9$
* $1 \leq q \leq 2 \times 10^5$
* $1 \leq a_i, b_i \leq 5000$ for each $1 \leq i \leq q$
* The sum of $\max(a_1, b_1, \dots, a_q, b_q)$ $\leq 5000$.

## Output

For each pairs, print an integer which denotes the result. 

<!--SAMPLES-->