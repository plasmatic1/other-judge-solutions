from random import *
from math import e

def sig(x):
    return 1 / (1 + e**x)

T = 100
N = 100
Q = 10000
# T = 10
# N = 10
# Q = 100
P = 0

with open('in', 'w') as fi:
    with open('exp', 'w') as fo:
        fi.write(f'{T}\n{P}\n')
        for _ in range(T):
            skill = [uniform(-3, 3) for _ in range(N)]
            diff = [uniform(-3, 3) for _ in range(Q)]
            ch = randint(0, N-1)

            for i in range(0, N):
                def getans(i, j):
                    return int(uniform(0, 1) <= sig(skill[i] - diff[j]))

                ans = []
                if i == ch:
                    for j in range(0, Q):
                        ans.append(getans(i, j) if randint(0, 1) == 0 else 1)
                else:
                    for j in range(0, Q):
                        ans.append(getans(i, j))

                fi.write(f'{"".join(map(str, ans))}\n')
            fo.write(f'Case #{_+1}: {ch+1}\n')

            print(f'Done case {_}')
