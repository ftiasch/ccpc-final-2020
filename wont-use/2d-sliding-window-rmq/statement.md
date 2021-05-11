# Range $k$-th Number

Bobo has a matrix $A$ with $n$ rows and $m$ columns. Given three parameters $h$, $w$ and $k$, let $M(i, j)$ be the $k$-th minimum number among the following $w \times h$ numbers
$$
\begin{matrix}
A_{i, j} & \dots & A_{i, j + w - 1} \\ 
\vdots & \ddots & \vdots \\
A_{i + h - 1, j} & \dots & A_{i + h - 1, j + w - 1} \\
\end{matrix}
$$
Namely, $M(i, j)$ is the $k$-th minimum number in the $h \times w$ sub-matrix starting from the $i$-th row and the $j$-the column.

Find the value of $M(i, j)$ for each $1 \leq i \leq n - h + 1$, $1 \leq j \leq m - w + 1$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains five integers $n$, $m$, $h$, $w$ and $k$.

For the following $n$ lines, the $i$-th line contains $m$ integers $A_{i, 1}, \dots, A_{i, m}$.

* $1 \le n, m \le 2000$
* $1 \leq h \leq n$
* $1 \leq w \leq m$
* $1 \leq k \leq \min\{h \cdot w, 5\}$
* $1 \leq A_{i, j} \leq 10^9$ for each $1 \leq i \leq n$, $1 \leq j \leq m$
* The sum of $n \cdot m$ $\leq 4 \times 10^6$

## Output

For each test case, output $(n - h + 1)$ lines. The $i$-th line contains $(m - w + 1)$ numbers $M(i, 1), \dots, M(i, m - w + 1)$.

<!--SAMPLES-->