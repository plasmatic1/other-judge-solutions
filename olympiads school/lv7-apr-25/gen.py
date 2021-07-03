from random import *

# N = 3
N = 5
# N = 10

print(N)
print(*[randint(0, N) for _ in range(N)])
print(*[randint(1, 10) for _ in range(N)])
