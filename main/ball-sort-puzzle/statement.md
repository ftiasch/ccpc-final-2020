---
timelimit: 1
...

# Stack

In compute science, a stack $s$ is a data structure maintaining a list of elements with two operations:

- $s.\mathtt{push}(e)$ which appends an element $e$ to the end of the list, and
- $s.\mathtt{pop}()$ which removes the most recently appended element that was not yet removed.

For convenience, Bobo denotes the number of elements in the stack by $s.\mathtt{size}$, and the last appended element by $s.\mathtt{top}$.

Bobo has $m$ stacks $s[1], \dots, s[m]$. Initially, the stack $s[i]$ contains $k_i$ elements $s[i][1], \dots, s[i][k_i]$. The elements in the stacks are from $\{1, \dots, n\}$, and each of the elements occurs exactly twice. Thus, $k_1 + \dots + k_m = 2 n$.

A sorting plan of length $l$ consists of $l$ pairs $(f_1, t_1), \dots, (f_l, t_l)$.  To execute a sorting plan, for each $i \in \{1, \dots ,l\}$ in the increasing order, Bobo ensures that

* $s[f_i].\mathtt{size} > 0$
* $s[t_i].\mathtt{size} < 2$
* either $s[t_i].\mathtt{size} = 0$ or $s[f_i].\mathtt{top} = s[t_i].\mathtt{top}$,

and performs $s[t_i].\mathtt{push}(s[f_i].\mathtt{pop}())$. A sorting plan is *valid* if the above conditions always hold and the length does not exceed $2n$.

Find a *valid* sorting plan such that after the execution each of the stacks either is empty of contains the two copies of the same element.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains two integers $n$ and $m$.

For the next $m$ lines, the $i$-th line contains an integer $k_i$, and $k_i$ integers $s[i][1], \dots, s[i][k_i]$.

* $1 \le n \leq m \le 2 \times 10^5$
* $0 \leq k_i \leq 2$ for each $1 \leq i \leq m$
* $k_1 + \dots + k_m = 2 n$
* $1 \leq s[i][j] \leq n$ for each $1 \leq i \leq m$, $1 \leq j \leq k_i$
* The sum of $m$ $\leq 2 \times 10^5$

## Output

For each test case, if there exists a *valid* sorting plan, output an integer $l$, which denotes the length of the sorting plan. Followed by $l$ lines, the $i$-th line contains two integers $f_i$ and $t_i$. Otherwise, output `-1`.

If there are multiple *valid* sorting plan, any of them is considered correct.

<!--SAMPLES-->

## Notes

For the first test cases,

* Initially, $s[1] = [1, 2]$, $s[2] = [1, 2]$, $s[3] = [\ ]$.
* After $s[3].\mathtt{push}(s[1].\mathtt{pop}())$. $s[1] = [1]$, $s[2] = [1, 2]$, $s[3] = [2]$.
* After $s[3].\mathtt{push}(s[2].\mathtt{pop}())$, $s[1] = [1]$, $s[2] = [1]$, $s[3] = [2, 2]$.
* After $s[1].\mathtt{push}(s[2].\mathtt{pop}())$, $s[1] = [1, 1]$, $s[2] = [\ ]$, $s[3] = [2, 2]$.

For the second test case, the initial configuration is already sorted.
