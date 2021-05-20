---
timelimit: 1
...

# How many Bobo(s)?

Bobo has an undirected graph with $n$ vertices and $m$ edges. The vertices are numbered by $1, \dots, n$, and the $i$-th edge is between the $a_i$-th and the $b_i$-th vertex. Plus, the $i$-th vertex is associated with a character $c_i$.

Find out the number of ways to choose four **distinct** vertices $\{u, v, w, x\}$ such that

* $u$ and $v$, $v$ and $w$, $w$ and $x$ are connected by an edge,
* $c_u = \mathtt{b}$, $c_v = \mathtt{o}$, $c_w = \mathtt{b}$, $c_x = \mathtt{o}$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $m$.

The second line contains $n$ characters $c_1 \dots c_n$.

For the following $m$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \le n \le 2 \times 10^5$
* $0 \le m \le 2 \times 10^5$
* $c_i \in \{\mathtt{b}, \mathtt{o}\}$ for each $1 \leq i \leq n$
* $1 \leq a_i, b_i \leq n$ for each $1 \leq i \leq m$
* $a_i \neq b_i$ for each $1 \leq i \leq m$
* $\{a_i, b_i\} \neq \{a_j, b_j\}$ for each $1 \leq i < j \leq m$

## Output

For each test case, output an integer which denotes the result.

<!--SAMPLES-->
