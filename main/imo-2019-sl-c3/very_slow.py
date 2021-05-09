def steps(s_):
    s = list(s_)
    result = 0
    while True:
        heads = s.count('H') - 1
        if heads == -1:
            break
        result += 1
        if s[heads] == 'H':
            s[heads] = 'T'
        else:
            s[heads] = 'H'
    return result

while True:
    try:
        input()
    except EOFError:
        break
    s = input()
    print(steps(s))
