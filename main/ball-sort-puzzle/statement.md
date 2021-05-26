---
timelimit: 1
...

# Data Structure

In compute science, a stack $s$ is a data structure maintaining a list of elements with two operations:

- $s.\mathtt{push}(e)$ appends an element $e$ to the right end of the list.
- $s.\mathtt{pop}()$ removes the rightmost element in the list and returns the removed element.

For convenience, Bobo denotes the number of elements in the stack by $\mathtt{size}(s)$, and the rightmost element by $\mathtt{right}(s)$.

Bobo has $m$ stacks $s_1, \dots, s_m$. Initially, the stack $s_i$ contains $k_i$ elements $a_{i, 1}, \dots, a_{i, k_i}$. The elements in the stacks are from $\{1, \dots, n\}$, and each of the elements occurs **exactly twice**. Thus, $k_1 + \dots + k_m = 2 n$.

A sorting plan of length $l$ consists of $l$ pairs $(f_1, t_1), \dots, (f_l, t_l)$.  To execute a sorting plan, for each $i \in \{1, \dots ,l\}$ in the increasing order, Bobo ensures that

* $\mathtt{size}(s_{f_i}) > 0$
* $\mathtt{size}(s_{t_i}) < 2$
* either $\mathtt{size}(s_{t_i}) = 0$ or $\mathtt{right}(s_{f_i}) = \mathtt{right}(s_{t_i})$,

and performs $s_{t_i}.\mathtt{push}(s_{f_i}.\mathtt{pop}())$. A sorting plan is *valid* if the above conditions always hold and the length does **not exceed** $\lfloor \frac{3n}{2} \rfloor$.

Find a *valid* sorting plan such that after the execution each of the stacks either is empty or contains the two copies of the same element.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains two integers $n$ and $m$.

For the next $m$ lines, the $i$-th line contains an integer $k_i$, and $k_i$ integers $a_{i, 1}, \dots, a_{i, k_i}$.

* $1 \le n \leq m \le 2 \times 10^5$
* $0 \leq k_i \leq 2$ for each $1 \leq i \leq m$
* $k_1 + \dots + k_m = 2 n$
* $1 \leq a_{i, j} \leq n$ for each $1 \leq i \leq m$, $1 \leq j \leq k_i$
* In each input, the sum of $m$ does not exceed $2 \times 10^5$.

## Output

For each test case, if there exists a *valid* sorting plan, output an integer $l$, which denotes the length of the sorting plan. Followed by $l$ lines, the $i$-th line contains two integers $f_i$ and $t_i$. Otherwise, output `-1`.

If there are multiple *valid* sorting plans, any of them is considered correct.

<!--SAMPLES-->

## Note

For the first test cases,

* Initially, $s_1 = [1, 2]$, $s_2 = [1, 2]$, $s_3 = [\ ]$.
* After $s_3.\mathtt{push}(s_1.\mathtt{pop}())$. $s_1 = [1]$, $s_2 = [1, 2]$, $s_3 = [2]$.
* After $s_3.\mathtt{push}(s_2.\mathtt{pop}())$, $s_1 = [1]$, $s_2 = [1]$, $s_3 = [2, 2]$.
* After $s_1.\mathtt{push}(s_2.\mathtt{pop}())$, $s_1 = [1, 1]$, $s_2 = [\ ]$, $s_3 = [2, 2]$.

For the second test case, the initial configuration is already sorted.
