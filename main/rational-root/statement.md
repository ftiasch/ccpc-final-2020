---
timelimit: 3
...

# Algebra

Given three integers $n$, $m$, $k$, find the number of pairs $(a, b)$ where

* $|a|, |b| \leq m$,
* $a, b \in \mathbb{Z}$, i.e., $a$ and $b$ are integers,
* $|S| = k$ where $S$ be the set of rational roots of the equation $x^n + a \cdot x + b = 0$, and $|S|$ is the size of $S$. In particular, there exists exactly $k$ **distinct rational** numbers $x$ which solve the last equation.

*Note*: $x$ is a rational number if and only if there exists two integers $p$ and $q$ ($q \neq 0$) where $x = \frac{p}{q}$.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains three integers $n$, $m$ and $k$.

* $1 \leq n, m, k \leq 5 \times 10^5$
* In each input, the sum of $m$ does not exceed $5 \times 10^5$.

## Output

For each test case, output an integer which denotes the number of pairs.

<!--SAMPLES-->

## Note

For the first test case, only the equation $x^2=0$ has one rational root.

For the second test case, each of the following $7$ equations has two distinct rational roots.

* $x^2-2x=0$
* $x^2-x=0$
* $x^2-x-2=0$
* $x^2-1=0$
* $x^2+x=0$
* $x^2+2x=0$
* $x^2+x-2=0$
