n = 10
x = 2
m = 6

def binom(n, k):
    if k == -1:
        if n == 0:
            return 1
        return 0
    result = 1
    for i in range(k):
        result = result * (n - i) // (i + 1)
    return result

def solve0(a, b):
    result = 0
    for i in range(n):
        if i >= a - 1 and n - 1 - i >= b - 1:
            result += pow(x, i - (a - 1)) * binom(i, a - 1) * pow(x + 1, (n - 1 - i) - (b - 1)) * binom(n - 1 - i, b - 1)
    return result

for a in range(m):
    print([solve0(a, b) for b in range(m)])

for a in range(1, m):
    print([solve0(a - 1, b) - solve0(a, b - 1) for b in range(1, m)])
