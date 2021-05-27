---
timelimit: 2
...

# Number Theory

Let $o_i = \underbrace{1 \dots 1}_{i\text{ times}}$ be the number which consists of $i$ ones in its decimal representation.

Bobo has an integer $n$. Find a sequence of possibly negative integers $(x_1, x_2, \dots, )$ where

* $\sum_{i = 1}^{\infty} o_i \cdot x_i = n$,
* $\sum_{i = 1}^{\infty} i \cdot |x_i|$ is minimized.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains an integer $n$.

* $1 \leq n < 10^{5000}$
* In each input, the sum of the number of decimal digits of $n$ does not exceed $50000$.

## Output

For each test case, output an integer which denotes the minimum value of $\sum_{i = 1}^\infty i \cdot |x_i|$.

<!--SAMPLES-->

## Note

For the first test case, $x_1 = x_2 = 1$, $x_3 = x_4 = \dots = 0$. The minimum value is $1 \times 1 + 2 \times 1 = 3$.

For the second test case, $x_1 = 0$, $x_2 = -1$, $x_3 = 1$, $x_4 = x_5 = \dots = 0$. The minimum value is  $2 \times 1 + 3 \times 1 = 5$.

