from random import *

N = 2000
M = N
Q = N

def p():
    a = randint(1, N)
    b = randint(1, N)
    if a > b: a, b = b, a
    return a, b

print(N, M, Q)
use = set()
for i in range(M):
    a, b = p()
    while a == b or (a, b) in use:
        a, b = p()
    use.add((a, b))
    print(a, b)
for i in range(Q):
    print(*p())
    # print(1, randint(1, N))

