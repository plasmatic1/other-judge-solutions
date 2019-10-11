import json

with open('names.txt') as f:
    names = json.loads('[' + f.read() + ']')

names.sort()
tot = 0
oa = ord('A')
for i, name in enumerate(names):
    tot += (i + 1) * sum([ord(c) - oa + 1 for c in name])

print(tot)