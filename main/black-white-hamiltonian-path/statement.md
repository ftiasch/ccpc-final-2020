# Hamiltonian Path

Given a complete undirected graph with $n$ vertices, each edge is colored either black or white.

Please find a permutation $p_0, p_1, \cdots, p_{n-1}$ of $\{1,2,\cdots,n\}$ such that there is at most one index $i$ ($1 \le i < n$) satisfying that the color of the edge connecting vertices $p_{i-1}$ and $p_i$ is different from the color of the edge connecting vertices $p_i$ and $p_{(i + 1) \bmod n}$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains an integer $n$ indicating the number of vertices.

For the following $n$ lines, the $i$-th line contains a string $c_{i,1}, c_{i,2}, \cdots, c_{i,n}$ where $c_{i,j}$ indicates the color of the edge connecting vertices $i$ and $j$ (`0` for black and `1` for white).

* $3 \le n \le 2000$
* $c_{i,j} \in \{\text{0}, \text{1}\}$
* $\forall 1 \le i, j \le n$, $c_{i,j}=c_{j,i}$
* $\forall 1 \le i \le n$, $c_{i,i}=0$
* The sum of $n$ $\leq 2000$

## Output

For each test case, output a permutation $p_0,p_1,\cdots,p_{n-1}$ separated in a single line if you can find any solutions. Otherwise, output $-1$ in a single line.

If there are multiple solutions, you can output any of them.

<!--SAMPLES-->
