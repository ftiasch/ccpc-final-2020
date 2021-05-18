---
timelimit: 1
...

# Almost Monochromatic Permutation

Bobo has an $n \times n$ symmetric matrix $C$ consisting of zeros and ones. For a permutation $p_1, \dots, p_n$ of $1, \dots, n$, let
$$
c_i = \begin{cases}
C_{p_i, p_{i + 1}} & \text{for } 1 \leq i < n \\
C_{p_n, p_1} & \text{for } i = n \\
\end{cases}
$$
The permutation $p$ is *almost monochromatic* if and only if the number of indices $i$ ($1 \leq i < n$) where $c_i \neq c_{i + 1}$ is at most one.

Find an *almost monochromatic* permutation $p_1, \dots, p_n$ for the given matrix $C$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains an integer $n$.

For the following $n$ lines, the $i$-th line contains $n$ integers $C_{i, 1}, \dots, C_{i, n}$.

* $3 \le n \le 2000$
* $C_{i, j} \in \{0, 1\}$ for each $1 \leq i, j \leq n$
* $C_{i, j} = C_{j, i}$ for each $1 \leq i, j \leq n$
* $C_{i, i} = 0$ for each $1 \leq i \leq n$
* The sum of $n$ $\leq 2000$

## Output

For each test case, if there exists an *almost monochromatic* permutation, output $n$ integers $p_1, \dots, p_n$ which denotes the permutation. Otherwise, output `-1`.

If there are multiple *almost monochromatic* permutations, any of them is considered correct.

<!--SAMPLES-->
