def multiply(a, b):
    c = [[0, 0], [0, 0]]
    for i in xrange(2):
        for j in xrange(2):
            for k in xrange(2):
                c[i][j] += a[i][k] * b[k][j]
            c[i][j] %= 7
    return c

read = lambda: map(int, raw_input().split())

while True:
    try:
        n = input()
    except EOFError:
        break
    a = [read(), read()]
    results = [[[1, 0], [0, 1]]]
    while n > 0:
        n -= 1
        results.append(multiply(results[-1], a))
        index = results.index(results[-1])
        if index < len(results) - 1:
            cycle = len(results) - 1 - index
            results.append(results[index + n % cycle])
    for row in results[-1]:
        print ' '.join(map(str, row))
