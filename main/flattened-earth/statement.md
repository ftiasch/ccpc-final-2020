# Flatten World

Bobo lives in a circular world. In this world, there are $n$ towns, numbered as $1, 2, \dots, n$. The $i$-th town is connected with the $(i+1)$-th town. Besides, the $1$-st town is connected with the $n$-th town.
He wants to remove one of these edges, so that this world would looks like a flattened one.
Also, he doesn't want this world changes too much. So he prepares $m$ pairs of towns. He wants to
make the maximum distance between these pairs as minimum as possible after the deletation.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $m$.

For the following $m$ line, the $i$-th contains two integers $a_i$ and $b_i$, indicating indexes of a town pair.

* $1 \leq n \leq 2 \times 10^5$
* $1 \leq m \leq 2 \times 10^5$
* $1 \leq a_i, b_i \leq n$ for each $1 \leq i \leq m$
* The sum of $n$ $\leq 2 \times 10^5$
* The sum of $m$ $\leq 2 \times 10^5$.

## Output

For each test case, output an integer which denotes the maximum distance between these pairs of
towns after the deletation.

<!--SAMPLES-->
