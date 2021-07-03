from random import *

N = 10
M = N
Q = N

def p():
    a = 1
    b = 1
    while a == b:
        a = randint(1, N)
        b = randint(1, N)
    if a > b: a, b = b, a
    return a, b

use = set()
print(N, M, Q)
print(''.join(choices(list('01'), k=N)))
for i in range(M):
    a, b = p()
    while (a, b) in use:
        a, b = p()
    use.add((a, b))
    print(a, b)
for i in range(Q):
    print(*p())
