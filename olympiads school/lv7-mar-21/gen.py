from random import randint
# R = 50000
# C = 50000
# Q = 100
R = 300000
C = R
Q = R
print(R, C, Q)
for i in range(Q):
    print(randint(1, R), randint(1, C))
