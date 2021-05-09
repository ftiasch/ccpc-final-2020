while True:
    try:
        s = input()
    except EOFError:
        break
    t = input()
    n = len(s)
    result = 0
    for i in range(n):
        st = s[:i] + t
        j = len(s) - 1
        while j > 0 and s[:j] != st[-j:]:
            j -= 1
        print(f'* $f({i}) = {j}$')
        result += i ^ j
    print(result)
