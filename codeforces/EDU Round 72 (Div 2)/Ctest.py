from random import *
from functools import partial

letf = partial(choice, list('01'))

t = 20
n = 100
ans = []
print(t)

for _ in range(t):
    s = ''.join(choices(list('01'), k=n))
    print(s)
    tot = 0
    for i in range(len(s)):
        for j in range(i, len(s)):
            # print(i, j, s[i:j+1])
            if int(''.join(s[i:j+1]), 2) == j - i + 1:
                tot += 1
    ans.append(tot)

print('--')
print('\n'.join(map(str, ans)))