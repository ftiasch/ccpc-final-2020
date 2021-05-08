while True:
    try:
        s = input()
    except EOFError:
        break
    d = {int(s): 0}
    inf = len(s) * len(s) * 20
    for i in range(len(s) + 10, 0, -1):
        d, e = {}, d
        u = 10**i//9
        for v, c in e.items():
            for x in range(-6, 7):
                t = x*u+v
                if abs(t) < u:
                    d[t] = min(c+i*abs(x), d.get(t, inf))
    print(d[0])
