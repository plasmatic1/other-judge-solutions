# ./append-sort.yml
# def csmall(s, t):
#     s = str(s)
#     t = str(t)
#     for i in range(min(len(s), len(t))):
#         if s[i] < t[i]: return True
#         elif s[i] > t[i]: return False
#     return False

def ispref(s, t):
    s = str(s)
    t = str(t)
    assert len(s) >= len(t)
    return s[0:len(t)] == t

for _tc in range(1, int(input())+1):
    pre = -1
    N = int(input())
    ans = 0
    for x in map(int, input().split()):
        nxt = x
        if x <= pre:
            a1 = x
            while a1 <= pre: a1 *= 10
            a2 = pre+1
            if ispref(a2, x):
                nxt = min(a1, a2)
            else:
                nxt = a1

        # print(f'N={N} nxt={nxt} x={x} pre={pre}')
        ans += max(0, len(str(nxt)) - len(str(x)))
        pre = nxt
    print(f'Case #{_tc}: {ans}')
