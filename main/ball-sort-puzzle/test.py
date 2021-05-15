#!/usr/bin/env python3


def search(balls, extra_stacks):
    state0 = tuple([(b, b) for b in range(balls)] + [()] * extra_stacks)
    states = set([state0])
    queue = [state0]
    stacks = balls + extra_stacks
    while queue:
        state = queue.pop()
        for dst in range(stacks):
            if len(state[dst]) == 1 or (len(state[dst]) == 2 and state[dst][0] == state[dst][1]):
                for src in range(stacks):
                    if src != dst and len(state[src]) < 2:
                        new_state = list(map(list, state))
                        elem = 
                        pass
    return states


print(search(3, 2))
