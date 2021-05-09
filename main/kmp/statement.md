# KMP Algorithm

In the classic string matching problem, a (short) pattern string $s$ and a (long) text string $t$ are given. It is required to determine whether the pattern appears somewhere in the text.

The KMP algorithm (Knuth-Morris-Pratt algorithm) is a well-known string matching algorithm to solve this problem. The key idea is to build a *prefix function* $\pi$ for the pattern string $s$, where $\pi(i)$ $(1 \le i \le |s|)$ is the length of the longest proper prefix of the substring $s[1..i]$. A proper prefix of a string is a prefix that is not equal to the string itself. By definition, $\pi(1) = 0$.

More formally,

$$
\pi(i)=\max_{0 \le k < i} \{k: s[1..k] = s[i-k+1..i]\}
$$

With this prefix function $\pi$, we can find all occurrences of $s$ in $t$ by the following pseudocode:

```
func match(s: string, t: string)
    let pi be the prefix function of s
    let occ be a bool array of length |t|
    i := 1
    j := 0
    while i <= |t|
        while j != 0 and s[j + 1] != t[i]
            j := pi[j]
        if s[j + 1] == t[i]
            j := j + 1
        if j == |s|
            occ[i - j + 1] := True
            j := pi[j]
        i := i + 1
    return occ
```

Bobo, a well-known string algorithm master, he has modified the algorithm above as follows:

```
func match2(s: string, t: string, j: integer)
    let pi be the prefix function of s
    i := 1
    while i <= |t|
        while j != 0 and s[j + 1] != t[i]
            j := pi[j]
        if s[j + 1] == t[i]
            j := j + 1
        if j == |s|
            j := pi[j]
        i := i + 1
    return j
```

Given two strings $s$ and $t$, Bobo would like to know the value of 

$$
\sum_{k=0}^{|s|-1} \mathrm{match2}(s, t, j) \oplus j
$$

where $\oplus$ is the exclusive or (XOR) bitwise operation.

## Input

The input consists of several test cases terminated by end-of-file.

The first line of each test case contains an string $s$ and the second line contains a string $t$.

* $1 \leq |s|, |t| \leq 10^6$
* Both $s$ and $t$ consist only of lowercase English letters.
* The sum of $\max(|s|, |t|)$ does not exceed $10^6$.

## Output

For each test case, print an integer which denotes the result.

<!--SAMPLES-->

## Note

For the first test case, the values of $\mathrm{match2}(s, t, j)$ are: $3\ 3\ 5\ 3\ 5\ 3\ 3\ 3\ 3\ 3$.

For the second test case, the values of $\mathrm{match2}(s, t, j)$ are: $6\ 6\ 6\ 6\ 6\ 6\ 6\ 6$.

For the third test case, the values of $\mathrm{match2}(s, t, j)$ are: $4\ 4\ 4\ 4\ 4\ 4\ 10\ 4\ 4\ 4\ 4\ 4\ 16\ 4\ 4\ 4\ 4$