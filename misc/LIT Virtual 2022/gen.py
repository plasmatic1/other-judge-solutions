from random import *

T = 1
V = 10
AL = list('abc')

print(T)
for _ in range(T):
    N = randint(1, V)
    M = randint(1, N)
    print(''.join((choice(AL) for _ in range(N))))
    print(''.join((choice(AL) for _ in range(M))))
