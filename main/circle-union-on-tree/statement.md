# Tree

Bobo has a tree with $n$ vertices. The $i$-th vertex has a weight $w_i$, and the $i$-th edge is between the $a_i$-th and $b_i$-th vertex.

Let $\delta(u, v)$ be the number of edges on the shortest path between the vertex $u$ and $v$, and $N(v, d) = \{u \mid \delta(u, v) \leq d \}$, i.e., the set of vertices whose distance to the vertex $v$ are not greater than $d$.

Bobo also has $q$ queries where the $i$-th query consists of $k_i$ tuples $(v_{i, 1}, d_{i, 1}), \dots, (v_{i, k_i}, d_{i, k_i})$. For the $i$-th query, let $U_i = N(v_{i, 1}, d_{i, 1}) \cup \dots \cup N(v_{i, k_i}, d_{i, k_i})$, i.e., the set of vertices $u$ where there exists a $1 \leq j \leq k_i$ such that $\delta(u, v_{i, j}) \leq d_{i, j}$. Find the value of $\sum_{v \in U_i} w_v$ (the sum of weight of vertices in $U_i$) for the $i$-th query.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $q$.

The second line contains $n$ integers $w_1, \dots, w_n$.

For the following $(n - 1)$ line, the $i$-th line contains two integers $a_i$ and $b_i$.

For the last $q$ line, the $i$-th line contains an integer $k_i$, followed by $2 \times k_i$ integers $v_{i, 1}, d_{i, 1}, \dots, v_{i, k_i}, d_{i, k_i}$.

For the following $n$ lines, the $i$-th line contains two integers $x_i, y_i$.

* $1 \leq n \leq 10^5$
* $1 \leq q \leq 10^5$
* $1 \leq w_i \leq 10^4$ for each $1 \leq i \leq n$
* $1 \leq a_i, b_i \leq n$ for each $1 \leq i \leq n - 1$
* $1 \leq k_i \leq n$ for each $1 \leq i \leq q$
* $1 \leq v_{i, j} \leq n$, $0 \leq d_{i, j} < n$ for each $1 \leq i \leq q$, $1 \leq j \leq k_i$
* The sum of $n$ $\leq 10^5$
* The sum of $q$ $\leq 10^5$
* The sum of $k_i$ $\leq 2 \times 10^5$.

## Output

For each queries, output an integer which denotes the result.

<!--SAMPLES-->