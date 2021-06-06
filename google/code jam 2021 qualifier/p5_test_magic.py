# test.yml
from math import e, sqrt

def sig(x): return 1 / (1 + e**(-x))

def avg(x):
    i = -3
    cnt = 0
    s = 0
    while i <= 3:
        s += sig(x-i)
        cnt += 1

        i += 0.01

    return s/cnt

# D=1.5
# D=(1+sqrt(5))/2
# D=1.75
# print(D)

def _ID(*x): pass
def test(D, print=_ID):
    print(f'testing D={D}')
    res = 0
    i = -3
    while i <= 3:
        reimann = avg(i)
        est = (sig(i-D) + sig(i+D)) / 2
        _D = reimann - est
        res += _D ** 4
        print(f'i={i} avg={reimann} hc={est}')
        i += 0.1
    print(f'Error: {res}')
    return res

# test(2, print)
# test(1.75, print)
# test(1, print)

l = 0
r = 3
eps = 10**-10
while l + eps < r:
    d = (r-l)/3
    m1 = l+d
    m2 = r-d
    r1 = test(m1)
    r2 = test(m2)
    if r1 < r2: r = m2
    else: l = m1

print(f'Got opt. D={l} with EPS={eps}')
test(l, print)
