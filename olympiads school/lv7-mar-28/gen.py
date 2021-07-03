from random import *

N = 20
M = N
V = N
E = V*V
# E = V-1

print(N, M, V, E)
print(*[randint(1, N) for _ in range(N)])
print(*[randint(1, N) for _ in range(N)])
print(*[round(uniform(0, 1), 1) for _ in range(N)])
# for i in range(V-1):
    # print(i+1,i+2,randint(1,10))
for i in range(E):
    print(randint(1, V), randint(1, V), randint(1, 10))
