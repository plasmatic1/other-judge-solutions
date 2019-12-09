s = input()
p = s.count('.')
e = s.count('!')

for ch in s:
    p += ch.islower()
    e += ch.isupper()

if p > e:
    print('Hi, Emily.')
else:
    print('Hi, Emily!')
