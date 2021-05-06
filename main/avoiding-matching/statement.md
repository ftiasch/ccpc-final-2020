# Matching

Bobo has a bipartite graph. The graph contains $(n + m)$ vertices $u_1, \dots, u_n$, $v_1, \dots, v_m$, and the edge between the vertex $u_i$ and $v_j$ is associated with weight $w_{i, j}$.

A set $M = \{(p_1, q_1), \dots, (p_k, q_k)\} \subseteq \{1, \dots n\} \times \{1, \dots, m\}$ is an *$(a, b)$-avoiding matching* if and only if

* For every $1 \leq i \leq k$, $p_i \neq a$.
* For every $1 \leq i \leq k$, $q_i \neq b$.
* For every $1 \leq i < j \leq k$, $p_i \neq p_j$.
* For every $1 \leq i < j \leq k$, $q_i \neq q_j$.

The weight of an $(a, b)$-avoiding matching $w(M) = w_{p_1, q_1} + \dots + w_{p_k, q_k} = \sum_{i = 1}^{k} w_{p_i, q_i}$. Let $\mathcal{M}_{a, b}$ be the set of all $(a, b)$-avoiding matching, and $f(a, b) = \max_{M \in \mathcal{M}_{a, b}} w(M)$.

Find each $1 \leq a \leq n$, $1 \leq b \leq m$, find the value of $f(a, b)$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $m$.

For the following $n$ lines, the $i$-th line contains $m$ integers $w_{i, 1}, \dots, w_{i, m}$.

* $2 \le n, m \le 500$
* $0 \le w(i, j) \le 10^6$ for each $1 \leq i \leq n$, $1 \leq j \leq m$
* The sum of $\max\{n, m\}$ $\leq 500$

## Output

For each test cases, output $n$ lines where the $i$-th line contains $m$ integers $f(i, 1), \dots, f(i, m)$.

<!--SAMPLES-->