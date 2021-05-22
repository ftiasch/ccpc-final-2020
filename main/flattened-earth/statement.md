---
timelimit: 1
...

# Cycle

Bobo has an **undirected** graph $G$ with $n$ vertices labeled by $1, \dots, n$ and $n$ edges. For each $1 \leq i \leq n$, there is an edge between the vertex $i$ and the vertex $(i \bmod n) + 1$. He also has a list of $m$ pairs $(a_1, b_1), \dots, (a_m, b_m)$.

Now, Bobo is going to remove the edge between the vertex $i$ and the vertex $(i \bmod n) + 1$.  Let $\delta_i(u, v)$ be the length of shortest path between the $u$-th and the $v$-th vertex **after the removal**. Choose an $i$ to minimize the maximum among $\delta_i(a_1, b_1), \dots, \delta_i(a_m, b_m)$.

Formally, find the value of
$$
\min_{1 \leq i \leq n}\left\{\max_{1 \leq j \leq m} \delta_i(a_j, b_j)\right\}
$$

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains two integers $n$ and $m$.

For the following $m$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \leq n \leq 2 \times 10^5$
* $1 \leq m \leq 2 \times 10^5$
* $1 \leq a_i, b_i \leq n$ for each $1 \leq i \leq m$
* The sum of $n$ $\leq 2 \times 10^5$
* The sum of $m$ $\leq 2 \times 10^5$

## Output

For each test case, output an integer which denotes the minimum value.

<!--SAMPLES-->

## Note

For the first case,

| $i$  | $\delta_i(1, 2)$ | $\delta_i(2, 3)$ | $\delta_i(3, 2)$ |
| ---- | ---------------- | ---------------- | ---------------- |
| $1$  | $2$              | $1$              | $1$              |
| $2$  | $1$              | $2$              | $2$              |
| $3$  | $1$              | $1$              | $1$              |

Choosing $i = 3$ yields the minimum value $1$.
