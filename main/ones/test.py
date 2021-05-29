import random


class Segment0:
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
    new_seg = Segment0(-1, [])
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
            new_seg = Segment0(s, [])
        else:
            new_seg.values.append(minv)
            s += 1
    return result


def trans0(length, pos, neg):
    pre_one = make_one(length + 1)
    cur_one = make_one(length)
    new_pos = []
    new_neg = []
    for seg in pos:
        s = seg.start
        k = s // cur_one
        r = s % cur_one
        new_pos_seg = Segment0(r, [])
        new_neg_seg = Segment0(r, [])
        for v in seg.values:
            new_pos_seg.values.append(v + k * length)
            new_neg_seg.values.append(v + (k + 1) * length)
            if r + 1 == cur_one:
                new_pos.append(new_pos_seg)
                new_neg.append(new_neg_seg)
                k += 1
                r = 0
                new_pos_seg = Segment0(0, [])
                new_neg_seg = Segment0(0, [])
            else:
                r += 1
        if new_pos_seg.values:
            new_pos.append(new_pos_seg)
            new_neg.append(new_neg_seg)
    for seg in neg:
        k = (pre_one - seg.start - 1) // cur_one
        r = (seg.start - pre_one) % cur_one
        new_pos_seg = Segment0(r, [])
        new_neg_seg = Segment0(r, [])
        for v in seg.values:
            new_neg_seg.values.append(v + k * length)
            new_pos_seg.values.append(v + (k + 1) * length)
            if r + 1 == cur_one:
                new_pos.append(new_pos_seg)
                new_neg.append(new_neg_seg)
                r = 0
                k -= 1
                new_pos_seg = Segment0(0, [])
                new_neg_seg = Segment0(0, [])
            else:
                r += 1
        if new_pos_seg.values:
            new_pos.append(new_pos_seg)
            new_neg.append(new_neg_seg)
    return merge(new_pos), merge(new_neg)


def solve0(n):
    pos = [Segment0(n, [0])]
    neg = []
    for length in range(len(str(n)) + 1, 0, -1):
        pos, neg = trans0(length, pos, neg)
        # if len(pos) == 1:
        #     print(pos[0].start, len(pos[0].values))
        # else:
        #     print(pos[1].start, len(pos[0].values) + len(pos[1].values))
        # print(pos)
    assert pos
    assert pos[0].start == 0
    return pos[0].values[0]


# DP_MAX = 10 ** 9
#
#
# def trans_large(length, start, positives, negatives):
#     one = make_one(length)
#     if start is not None:
#         assert len(positives) + 1 < one
#         r = start % one
#         k = start // one
#         one_minus_r = min(one - r, len(positives) + 1)
#         if r <= 1:
#             assert len(positives) < one_minus_r
#             # becomes prefix
#         elif len(positives) == one_minus_r:
#             # becomes suffix
#             pass
#         elif len(positives) > one_minus_r:
#             # becomes prefix + suffix
#             pass
#         else:
#             size = len(positives) + 1
#             kpositives = [DP_MAX] * size
#             knegatives = [DP_MAX] * size
#             for i, v in enumerate(positives):
#                 kpositives[i + 1] = min(kpositives[i + 1], v + k * length)
#                 knegatives[i + 1] = min(knegatives[i + 1],
#                                         v + (k + 1) * length)
#             for i, v in enumerate(negatives):
#                 knegatives[i] = min(knegatives[i], v + (9 - k) * length)
#                 kpositives[i] = min(kpositives[i], v + (10 - k) * length)
#             return r - 1, kpositives, knegatives
#     else:
#         pprefix, psuffix = positives
#         nprefix, nsuffix = negatives
#         kprefix_size = max(len(pprefix), 1)
#         kpprefix = [DP_MAX] * kprefix_size
#         knprefix = [DP_MAX] * kprefix_size
#         ksuffix_size = max(len(nsuffix), 1)
#         kpsuffix = [DP_MAX] * ksuffix_size
#         knsuffix = [DP_MAX] * ksuffix_size
#         assert kprefix_size + ksuffix_size < one
#         for i, v in enumerate(pprefix):
#             kpprefix[i] = min(kpprefix[i], v)
#             knprefix[i] = min(knprefix[i], v + length)
#         if psuffix:
#             kpprefix[0] = min(kpprefix[0], psuffix[0] + 10 * length)
#             knprefix[0] = min(knprefix[0], psuffix[0] + 11 * length)
#             for i, v in enumerate(pprefix):
#                 if i > 0:
#                     kpsuffix[i - 1] = min(kpsuffix[i - 1], v + 9 * length)
#                     knsuffix[i - 1] = min(knsuffix[i - 1], v + 10 * length)
#         for i, v in enumerate(nsuffix):
#             knsuffix[i] = min(knsuffix[i], v)
#             kpsuffix[i] = min(kpsuffix[i], v + length)
#         if nprefix:
#             knsuffix[0] = min(knsuffix[0], v + 10 * length)
#             kpsuffix[0] = min(kpsuffix[0], v + 11 * length)
#             for i, v in enumerate(nprefix):
#                 if i > 0:
#                     knprefix[i - 1] = min(knprefix[i - 1], v + 9 * length)
#                     kpprefix[i - 1] = min(kpprefix[i - 1], v + 10 * length)
#         return None, (kpprefix, kpsuffix), (knprefix, knsuffix)
#
#
# def solve(n):
#     # dp_start = n
#     # pdp = [0]
#     # ndp = [0]
#     length = len(str(n))
#     one = make_one(length + 1)
#     positives = [0]
#     negatives = [length + 1]
#     start = n
#     while length > 0:
#         trans_large(length, start, positives, negatives)
#
# def gen_seg0(pre_one, dp_length, r):
#     if r + dp_length <= pre_one:
#         values = [random.randint(1, 100) for i in range(dp_length)]
#         return [Segment0(r, values)]
#     prefix_length = pre_one - r
#     suffix_length = dp_length - prefix_length
#     prefix_values = [random.randint(1, 100) for i in range(prefix_length)]
#     suffix_values = [random.randint(1, 100) for i in range(suffix_length)]
#     return [Segment0(0, prefix_values), Segment0(r, suffix_values)]

def solve0_start(n):
    pos = [Segment0(n, [0])]
    neg = []
    starts = []
    for length in range(len(str(n)) + 1, 0, -1):
        pos, neg = trans0(length, pos, neg)
        if len(pos) == 1:
            starts.append(pos[0].start)
            # print(pos[0].start, len(pos[0].values))
        else:
            starts.append(pos[1].start)
    return starts

def solve_start(n):
    r = n + 1
    starts = []
    for length in range(len(str(n)) + 1, 0, -1):
        one = make_one(length)
        r = (r + one - 1) % one
        starts.append(r)
    return starts


if __name__ == '__main__':
    for n in range(1, 10 ** 5):
        assert solve0_start(n) == solve_start(n)
