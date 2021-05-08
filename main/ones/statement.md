# 1...1

Let $o_i = \underbrace{1 \dots 1}_{i\text{ times}}$ be the number which consists of $i$ ones in the decimal representation.

Bobo has an integer $n$. Let $(x_1, x_2, \dots, )$ be a sequence of (possibly negative) integers where 
$$
n = \sum_{i = 1}^{\infty} o_i \cdot x_i
$$
Find the minimum value of $\sum_{i = 1}^{\infty} i \cdot |x_i|$.

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains an integer $n$.

* $1 \leq n < 10^{5000}$
* The sum of decimal digits of $n$ $\leq 5000$

## Output

For each test case, output an integer which denotes the result.

<!--SAMPLES-->

## Note

For the first test case, $x_1 = 3$, $x_2 = x_3 = \dots = 0$. The minimum value is $1 \times 3 = 3$.

For the second test case, $x_1 = 0$, $x_2 = -1$, $x_3 = 1$, $x_4 = x_5 = \dots = 0$. The minimum value is  $1 \times 2 + 1 \times 3 = 5$.