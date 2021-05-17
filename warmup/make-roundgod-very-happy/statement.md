# Make Rounddog *Very* Happy

*The task is adapted from HDOJ 6701 - Make Rounddog Happy*.

Bobo has a sequence of integers $a_1, a_2, \dots, a_n$ and an integer $m$. 

Let $f(j)$ be the number of $i$ where $1 \leq i \leq j$ and $\max\{a_i, \dots, a_j\} - (j - i + 1) \geq m$ hold. Find the value of $f(1), \dots, f(n)$.

## Input

The input consists of several test cases terminated by end-of-file.

The first line of each test case contains two integers $n$ and $m$, and the second line contains $n$ integers $a_1, a_2, \dots, a_n$.

* $1 \leq n \leq 10^6$
* $-n \leq m \leq n$
* $1 \leq a_i \leq n$
* The sum of $n$ does not exceed $5 \times 10^6$.

## Output

For each test case, print $n$ integers $f(1), \dots, f(n)$.

<!--SAMPLES-->
