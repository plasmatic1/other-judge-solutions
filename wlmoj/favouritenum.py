LIM = 75
n = []

for i in range(LIM + 1):
    for j in range(LIM + 1):
        n.append((2 ** i) * (3 ** j))

n.sort()

i = int(input())
print(n[i - 1])
