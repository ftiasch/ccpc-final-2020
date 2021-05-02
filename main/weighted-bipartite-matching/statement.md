# Weighted Bipartite Matching

Bobo has a bipartite graph. The left part of this graph contains $n$ vertices and the right part contains $m$ vertices. The weight between the $i$-th vertex in the left part and the $j$-th vertex in the right part is $w(i,j)$.

For each $1 \le u \le n$ and $1 \le v \le m$, Bobo would like to know the **maximum weighted bipartite matching** after deleting the $u$-th vertex in the left part and the $v$-th vertex in the second part.

## Input

The input consists of several test cases terminated by end-of-file.

The first line contains two integers $n$ and $m$ -- number of vertices in the left and right part.

Each of the next $n$ lines contains $m$ integers $w(i,1), w(i,2), \dots, w(i,m)$.

* $2 \le n, m \le 500$
* $0 \le w(i, j) \le 10^6$
* There are no more than $3$ test cases such that $\max(n, m) > 200$.

## Output

For each test case, output $n$ lines and each contains $m$ integers. The $v$-th integer in the $u$-th line is the sum of weights of **maximum weighted bipartite matching** after deleting the $u$-th vertex in the left part and the $v$-th vertex in the second part.

<!--SAMPLES-->
