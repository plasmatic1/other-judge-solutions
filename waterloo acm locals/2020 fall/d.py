# d.yml
from collections import *
n = int(input())

names = {}
clist = []
lines = []

for i in range(n):
    sl = input().replace(' allows travellers from', '').split()
    lines.append(sl)
    names[sl[0]] = i
    clist.append(sl[0])

g = [[] for _ in range(n)]
dis = [0] * n

for sl in lines:
    for goto in sl[1:]:
        # print(f'goto={goto}, rv={recv(goto)}, rv2={recv(sl[0])}')
        g[names[goto]].append(names[sl[0]])

q = deque()
dis[0] = 1
q.append(0)

# print(g)

while q:
    c = q.popleft()
    for to in g[c]:
        if not dis[to]:
            dis[to] = dis[c] + 1
            q.append(to)

out = []
for i in range(n):
    out.append((clist[i], dis[i]))
out.sort()
for name, d in out:
    print(d)
