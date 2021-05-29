#!/usr/bin/env python
import argparse
import random

def make_one(n):
    return (10 ** n - 1) // 9

# def find(n):
#     r = n + 1
#     starts = []
#     for length in range(len(str(n)) + 1, 0, -1):
#         one = make_one(length)
#         r = (r + one - 1) % one
#         starts.append(r)
#     return starts

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-T', type=int, required=True)
    parser.add_argument('-n', type=int, required=True)
    parser.add_argument('-s', type=int, required=True)
    args = parser.parse_args()
    T = args.T
    random.seed(args.s)
    n = args.n
    while T > 0:
        T -= 1
        n0 = random.randint(1, n - 2)
        r = random.randint(0, n0)
        for length in range(n0, n - 1):
            one = make_one(length)
            r = (r + 1) % one
            if r == 0:
                k = random.randint(0, 10)
            else:
                k = random.randint(0, 9)
            r += one * k
        print(r)
