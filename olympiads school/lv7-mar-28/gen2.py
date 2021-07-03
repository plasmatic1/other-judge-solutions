from random import *

N = 200000
M = 1
print(N, M)
for i in range(1, N):
    print(randint(1, i), i+1)
print(*[randint(1, M) for _ in range(N)])
