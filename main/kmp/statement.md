# Prefix Suffix

For a string $u = u_1 \dots u_n$, Bobo denotes the prefix $u_1 \dots u_i$ by $\mathrm{pre}(u, i)$. Similarly, he denotes the suffix $u_{n - i + 1} \dots u_n$ by $\mathrm{suf}(u, i)$. In particular, $\mathrm{pre}(u, 0)$ and $\mathrm{suf}(u, 0)$ are empty strings. 

For two strings $u = u_1 \dots u_n$ and $v = v_1 \dots v_m$, Bobo denotes denotes the concatenation of  $u_1 \dots u_n v_1 \dots v_m$ by $u + v$. Also, 
$$
\mathrm{presuf}(u, v) = \max\{i \mid i < n \text{ and } \mathrm{pre}(u, i) = \mathrm{suf}(v, i) \}
$$
Given two strings $s = s_1 \dots s_n$ and $t = t_1 \dots t_m$, let $f(i) = \mathrm{presuf}(s, \mathrm{pre}(s, i) + t)$. 

Find the value of $\sum_{i = 0}^{n - 1} f(i) \oplus i$ where $\oplus$ denotes the bitwise exclusive-or (XOR).

## Input

The input consists of several test cases terminated by end-of-file. For each test cases,

The first line contains a string $s_1 \dots s_n$.

The second line contains a string $t_1 \dots t_m$.

* $1 \leq n, m \leq 10^6$
* $s_i \in \{a, \dots, z\}$ for each $1 \leq i \leq n$
* $t_i \in \{a, \dots, z\}$ for each $1 \leq i \leq m$
* The sum of $\max(n, m)$ $\leq 10^6$.

## Output

For each test case, print an integer which denotes the result. 

<!--SAMPLES-->

## Note

For the first test case, the value of $f$ is shown below.

* $f(0) = 3$
* $f(1) = 3$
* $f(2) = 5$
* $f(3) = 3$
* $f(4) = 5$
* $f(5) = 3$
* $f(6) = 3$
* $f(7) = 3$
* $f(8) = 3$
* $f(9) = 3$