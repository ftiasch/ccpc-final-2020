---
timelimit: 1
...

# Game Theory

For a string $s_1\dots s_n$ of bits (i.e., zeros and ones), Bobo computes the $f$-value of $s_1\dots s_n$ by playing the following game.

* If all the bits are zero, the game ends.
* If there are $k$ ones in the bit string, Bobo flips the $k$-th bit, i.e., $s_k$.
* The $f$-value of the bit string is the number of flips Bobo has performed before the game ends.

Formally,

* If $s_1 = \dots = s_n = 0$, $f(s_1 \dots s_n) = 0$.
* Otherwise, assuming that $k = s_1 + \dots + s_n$, $f(s_1 \dots s_n) = f(s_1 \dots s_{k - 1} \overline{s_k} s_{k + 1} \dots s_n) + 1$ where $\overline{c}$ denotes the flip of the bit $c$ such as $\overline{0} = 1$ and $\overline{1} = 0$.

Now, Bobo has a bit string $s_1 \dots s_n$ subjecting to $q$ changes, where the $i$-th change is to flip all the bits among $s_{l_i} \dots s_{r_i}$ for given $l_i$, $r_i$. Find the $f$-value **modulo** $998244353$ of the bit string after each change.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains two integers $n$ and $q$.

The second line contains $n$ bits $s_1 \dots s_n$.

For the following $q$ lines, the $i$-th line contains two integers $l_i$ and  $r_i$.

* $1 \le n \le 2 \times 10^5$
* $1 \le q \le 2 \times 10^5$
* $s_i \in \{0, 1\}$ for each $1 \leq i \leq n$
* $1 \leq l_i \leq r_i \leq n$ for each $1 \leq i \leq q$
* In each input, the sum of $n$ does not exceed $2 \times 10^5$. The sum of $q$ does not exceed $2 \times 10^5$.

## Output

For each change, output an integer which denotes the $f$-value modulo $998244353$.

<!--SAMPLES-->

## Notes

For the first test case, the string becomes `100` after the first change. $f(\texttt{100}) = f(\texttt{000}) + 1 = 1$. And it becomes `111` after the second change. $f(\texttt{111}) = f(\texttt{110}) + 1 = f(\texttt{100}) + 2 = f(\texttt{000}) + 3 = 3$.
