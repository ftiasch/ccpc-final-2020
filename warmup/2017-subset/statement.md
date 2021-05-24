---
timelimit: 2
...

# 2017

Bobo has a set of $n$ integers $A=\{a_1, \dots, a_n\}$. Given an integer $r$, find the number of **non-empty** subsets of $A$ whose **product**'s remainder divided by $2017$ is $r$.

As the exact number is large, find the number **modulo** $2$ instead.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains two integers $n$, $r$.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$.

* $1 \leq n \leq 2\times 10^6$
* $1 \leq r < 2017$
* $1 \leq a_i < 2017$ for each $1 \leq i \leq n$
* In each input, the number of test cases does not exceed $10^4$. The sum of $n$ does not exceed $2 \times 10^6$.

## Output

For each test case, output an integer which denotes the parity.

<!--SAMPLES-->
