---
timelimit: 1
...

# 2020

Bobo has a string $s_1 \dots s_n$ of length $n$ consisting of only digits $0$, $1$, $2$, and he wants to pick some **disjoint** **subsequences** which equal to $2020$, as many as possible.

Formally, Bobo would like to find $k$ quadrangles $(a_1, b_1, c_1, d_1), \dots, (a_k, b_k, c_k, d_k)$ where

* $1 \leq a_i < b_i < c_i < d_i \leq n$ for each $1 \leq i \leq k$
* $s_{a_i} s_{b_i} s_{c_i} s_{d_i} = 2020$ for each $1 \leq i \leq k$
* $\{a_i, b_i, c_i, d_i\} \cap \{a_j, b_j, c_j, d_j\} = \emptyset$ for each $1 \leq i < j \leq k$.

Find the maximum value of $k$.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains an integer $n$.

The second line contains a string $s_1 \dots s_n$.

* $1 \leq n \leq 2 \times 10^5$
* $s_i \in \{0, 1, 2\}$ for each $1 \leq i \leq n$
* In each input, the sum of $n$ does not exceed $2 \times 10^5$.

## Output

For each test case, output an integer which denotes the result.

<!--SAMPLES-->
