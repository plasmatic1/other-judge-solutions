from random import *

# N = 7
# K = 3
N = 500
K = 10

print(N, K)
for i in range(N-1):
    print(i+1, i+2)

ls = list(range(1, K+1))
while len(ls) < N: ls.append(randint(1, K))
shuffle(ls)
for x in ls:
    print(x)
