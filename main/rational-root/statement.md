---
timelimit: 3
...

# Rational Root

Given $n$, $m$, $k$, find the number of pairs $(a, b)$ such that

* $a, b \in \mathbb{Z}$, i.e., $a$ and $b$ are integers
* $|a|, |b| \leq m$
* $|S| = k$, where $S$ be the set of rational roots of the equation $x^n + a \cdot x + b = 0$. In particular, there exists exactly $k$ *distinct* *rational* numbers $x$ which solves the last equation.

Note that $x$ is a rational number if and only if there exists integers $p$ and $q$ ($q \neq 0$) where $x = \frac{p}{q}$.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains three integers $n$, $m$ and $k$.

* $1 \leq n, m, k \leq 5 \times 10^5$
* In each input, the sum of $m$ does not exceed $5 \times 10^5$.

## Output

For each test case, output an integer which denotes the number of pairs.

<!--SAMPLES-->

## Notes

For the first test case, except for $a=-1$, all other equations have exactly $1$ rational root $-\frac{b}{a+1}$.

For the second test case, only equation $x^2=0$ has $1$ rational root $0$.

For the third test case, there $7$ equations: $x^2-2x=0$, $x^2-x=0$, $x^2-x-2=0$, $x^2-1=0$, $x^2+x=0$, $x^2+2x=0$, and $x^2+x-2=0$.
