import random

class Segment:
    def __init__(self, start, values):
        self.start = start
        self.values = values

    def __repr__(self):
        return repr((self.start, self.values))

    def get(self, i):
        if i < self.start or self.start + len(self.values) <= i:
            return None
        return self.values[i - self.start]


def make_one(n):
    return (10 ** n - 1) // 9


INF = 10 ** 100


def merge(segs):
    result = []
    s = -1
    new_seg = Segment(-1, [])
    while True:
        minv = INF
        for seg in segs:
            v = seg.get(s)
            if v is not None:
                minv = min(minv, v)
        if minv == INF:
            if new_seg.values:
                result.append(new_seg)
            ns = INF
            for seg in segs:
                if s < seg.start:
                    ns = min(ns, seg.start)
            if ns == INF:
                break
            s = ns
            new_seg = Segment(s, [])
        else:
            new_seg.values.append(minv)
            s += 1
    return result


def solve0(n):
    pos = [Segment(n, [0])]
    neg = []
    for length in range(len(str(n)) + 1, 0, -1):
        pre_one = make_one(length + 1)
        cur_one = make_one(length)
        new_pos = []
        new_neg = []
        for seg in pos:
            s = seg.start
            k = s // cur_one
            r = s % cur_one
            new_pos_seg = Segment(r, [])
            new_neg_seg = Segment(r, [])
            for v in seg.values:
                new_pos_seg.values.append(v + k * length)
                new_neg_seg.values.append(v + (k + 1) * length)
                if r + 1 == cur_one:
                    new_pos.append(new_pos_seg)
                    new_neg.append(new_neg_seg)
                    k += 1
                    r = 0
                    new_pos_seg = Segment(0, [])
                    new_neg_seg = Segment(0, [])
                else:
                    r += 1
            if new_pos_seg.values:
                new_pos.append(new_pos_seg)
                new_neg.append(new_neg_seg)
        for seg in neg:
            k = (pre_one - seg.start - 1) // cur_one
            r = (seg.start - pre_one) % cur_one
            new_pos_seg = Segment(r, [])
            new_neg_seg = Segment(r, [])
            for v in seg.values:
                new_neg_seg.values.append(v + k * length)
                new_pos_seg.values.append(v + (k + 1) * length)
                if r + 1 == cur_one:
                    new_pos.append(new_pos_seg)
                    new_neg.append(new_neg_seg)
                    r = 0
                    k -= 1
                    new_pos_seg = Segment(0, [])
                    new_neg_seg = Segment(0, [])
                else:
                    r += 1
            if new_pos_seg.values:
                new_pos.append(new_pos_seg)
                new_neg.append(new_neg_seg)
        pos = merge(new_pos)
        neg = merge(new_neg)
        print( pos, neg)
    assert pos
    assert pos[0].start == 0
    return pos[0].values[0]

DP_MAX = 10 ** 9
def solve(n):
    # dp_start = n
    # pdp = [0]
    # ndp = [0]
    one_length = len(str(n)) + 1
    one = make_one(one_length)
    pdp = [0]
    ndp = [len(str(n)) + 1]
    dp_start = n
    dp_reset = 1
    one_length -= 1
    one //= 10
    print(dp_start, pdp, ndp)
    while one_length > 0:
        next_pdp = [DP_MAX] * (len(pdp) + 1)
        next_ndp = [DP_MAX] * (len(ndp) + 1)

        remainder = dp_start % one

        pk = dp_start // one
        pr = remainder
        if remainder == 0:
            nk = 10 - pk
            nr = one - 1
        else:
            nk = 9 - pk
            nr = remainder - 1
        dp_start = nr
        for i, v in enumerate(pdp):
            if i == dp_reset:
                pk = 0
                pr = 0
            index = (1 + i) % one
            next_pdp[index] = min(next_pdp[index], v + pk * one_length)
            next_ndp[index] = min(next_ndp[index], v + (pk + 1) * one_length)
            pr += 1
            if pr == one:
                pk += 1
        for i, v in enumerate(ndp):
            if i == dp_reset:
                nk = 10
                nr = one - 1
            index = i % one
            next_ndp[index] = min(next_ndp[index], v + nk * one_length)
            next_pdp[index] = min(next_pdp[index], v + (nk + 1) * one_length)
            nr += 1
            if nr == one:
                nk -= 1

        pdp = next_pdp
        ndp = next_ndp
        if remainder == 0:
            dp_reset = 1
        else:
            dp_reset += 1
        print(dp_reset, dp_start, pdp, ndp)

        one_length -= 1
        one //= 10
    return pdp[0]

if __name__ == '__main__':
    random.seed(0)
    n = 11111
    solve0(n)
    print('---')
    # solve(n)
    # for n in range(1, 10000):
    #     print('n=', n)
    #     assert solve0(n) == solve(n)
