# Root

For a fixed $n$ and integers $p$ and $q$ such that $|p| \le m$ and $|q| \le m$, how many equations of the form

$$
x^n+px+q=0
$$

have exactly $k$ rational root?

Note that $x$ is a rational root of $x^n+px+q=0$, if it can be written in the form $\frac{a}{b}$ ($b \ne 0$), where $a$ and $b$ are integers.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains three integers $n$, $m$ and $k$.

* $1 \leq n, m, k \leq 5 \times 10^5$
* The sum of $m \leq 5 \times 10^5$

## Output

For each test case, output an integer denoting the answer.

<!--SAMPLES-->

## Notes

For the first test case, except for $p=-1$, all other equations have exactly $1$ rational root $-\frac{q}{p+1}$.

For the second test case, only equation $x^2=0$ has $1$ rational root $0$.

For the third test case, there $7$ equations: $x^2-2x=0$, $x^2-x=0$, $x^2-x-2=0$, $x^2-1=0$, $x^2+x=0$, $x^2+2x=0$, and $x^2+x-2=0$.