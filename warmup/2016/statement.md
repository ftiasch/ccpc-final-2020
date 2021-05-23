---
timelimit: 2
...

# 2016

Given a $2 \times 2$ matrix
$$
A = \begin{pmatrix}
    a_{11} & a_{12} \\
    a_{21} & a_{22} \\
\end{pmatrix},
$$
find $A^n$ **modulo** $7$ where $A^1 = A, A^n = A \times A^{n - 1}$.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains an integer $n$.

The second line contains two integers $a_{11}, a_{12}$.

The third line contains two integers $a_{21}, a_{22}$.

* $1 \leq n < 10^{100000}$
* $0 \leq a_{ij} < 7$ for each $1 \leq i \leq 2, 1 \leq j \leq 2$
* $(a_{11} a_{22} - a_{12} a_{21}) \bmod 7 \neq 0$
* In each input, the number of test cases does not exceed $10^4$. The sum of the number of decimal digits of $n$ does not exceed $10^5$.

## Output

For each test case, output a $2 \times 2$ matrix which denotes the result.

<!--SAMPLES-->
