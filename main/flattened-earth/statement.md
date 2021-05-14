# Circular World

Bobo lives in a circular world. In the world, there are $n$ towns numbered by $1, \dots, n$. The $i$-th ($1 \leq i \leq n - 1$) town is connected with the $(i+1)$-th town by a bidirectional road. Besides, the $n$-th town is connected with the $1$-st town by a bidirectional road.

Bobo is going to remove exactly one of these $n$ roads. He also knows $m$ pairs of towns $(a_1, b_1), \dots, (a_m, b_m)$.

He wants to remove one of these edges, so that this world would looks like a flattened one.
Also, he doesn't want this world changes too much. So he prepares $m$ pairs of towns. He wants to
make the maximum distance between these pairs as minimum as possible after the deletation.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $m$.

For the following $m$ lines, the $i$-th line contains two integers $a_i$ and $b_i$.

* $1 \leq n \leq 2 \times 10^5$
* $1 \leq m \leq 2 \times 10^5$
* $1 \leq a_i, b_i \leq n$ for each $1 \leq i \leq m$
* The sum of $n$ $\leq 2 \times 10^5$
* The sum of $m$ $\leq 2 \times 10^5$

## Output

For each test case, output an integer which denotes the result.

<!--SAMPLES-->
