def steps(s):
    result = 0
    for i, c in enumerate(s):
        if c == 'H':
            result += 2 * (i + 1)
    k = s.count('H')
    return result - k * k

while True:
    try:
        input()
    except EOFError:
        break
    s = input()
    print(steps(s))
