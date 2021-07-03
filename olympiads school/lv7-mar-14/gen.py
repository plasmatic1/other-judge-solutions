from random import *
T=1
N=6

print(T)
for i in range(T):
    print(N, N-1)
    for j in range(2,N+1):
        print(randint(1,j-1),j)
