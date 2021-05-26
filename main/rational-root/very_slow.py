#!/usr/bin/env python3
def divisors(a):
    roots = []
    for x in range(1, abs(a) + 1):
        if a % x == 0:
            roots.append(x)
            roots.append(-x)
    return roots

def solve(n, m, k):
    result = 0
    if n == 1:
        for a in range(-m, m + 1):
            for b in range(-m, m + 1):
                roots = 0
                if a + 1 == 0:
                    if b == 0:
                        roots = k + 1
                    else:
                        roots = 0
                else:
                    roots += 1
                if roots == k:
                    result += 1
        return result
    else:
        for a in range(-m, m + 1):
            for b in range(-m, m + 1):
                roots = 0
                if b == 0:
                    roots += 1
                    if a != 0:
                        for x in divisors(a):
                            if pow(x, n - 1) + a == 0:
                                roots += 1
                else:
                    for x in divisors(b):
                        if pow(x, n) + a * x + b == 0:
                            roots += 1
                if roots == k:
                    result += 1
        return result

while True:
    try:
        n, m, k = list(map(int, input().split()))
    except EOFError:
        break
    print(solve(n, m, k))
