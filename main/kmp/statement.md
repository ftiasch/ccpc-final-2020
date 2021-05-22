---
timelimit: 1
...

# Prefix and Suffix

For a string $u = u_1 \dots u_n$, Bobo denotes the prefix $u_1 \dots u_i$ by $\mathrm{pre}(u, i)$. Similarly, he denotes the suffix $u_{n - i + 1} \dots u_n$ by $\mathrm{suf}(u, i)$. In particular, $\mathrm{pre}(u, 0)$ and $\mathrm{suf}(u, 0)$ are empty strings.

For two strings $u = u_1 \dots u_n$ and $v = v_1 \dots v_m$, Bobo denotes denotes the concatenation of  $u_1 \dots u_n v_1 \dots v_m$ by $u + v$. Also,
$$
\mathrm{presuf}(u, v) = \max\{i \mid i < n \text{ and } i \leq m \text{ and } \mathrm{pre}(u, i) = \mathrm{suf}(v, i) \}
$$

Given two strings $s = s_1 \dots s_n$ and $t = t_1 \dots t_m$, let $f(i) = \mathrm{presuf}(s, \mathrm{pre}(s, i) + t)$. Find the value of $f(0), \dots, f(n - 1)$.

## Input

The input consists of several test cases terminated by end-of-file. For each test case,

The first line contains a string $s_1 \dots s_n$.

The second line contains a string $t_1 \dots t_m$.

* $1 \leq n, m \leq 10^6$
* $s_i \in \{a, \dots, z\}$ for each $1 \leq i \leq n$
* $t_i \in \{a, \dots, z\}$ for each $1 \leq i \leq m$
* The sum of $\max(n, m)$ $\leq 10^6$.

## Output

For each test case, print $n$ integers which denote $f(0), \dots, f(n - 1)$.

<!--SAMPLES-->

## Note

For the second case, $f(4) = \mathrm{presuf}(s, \mathrm{pre}(s, 4) + t) = \mathrm{presuf}(\texttt{ababa}, \texttt{abab} + \texttt{a}) = \mathrm{presuf}(\texttt{ababa}, \texttt{ababa})$.

| $i$  | $\mathrm{pre}(\mathtt{ababa}, i)$ | $\mathrm{suf}(\mathtt{ababa}, i)$ |
| ---- | --------------------------------- | --------------------------------- |
| $0$  | (an empty string)                 | (an empty string)                 |
| $1$  | $\mathtt{a}$                      | $\mathtt{a}$                      |
| $2$  | $\mathtt{ab}$                     | $\mathtt{ba}$                     |
| $3$  | $\mathtt{aba}$                    | $\mathtt{aba}$                    |
| $4$  | $\mathtt{abab}$                   | $\mathtt{baba}$                   |

Therefore, $f(4) = 3$.
