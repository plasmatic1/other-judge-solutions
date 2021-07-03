from random import *

lets = list('abcd')

N = randint(1, 2000)
K = randint(1, N)

print(N, K)
print(''.join(choices(lets, k=N)))
print(''.join(choices(lets, k=N)))
