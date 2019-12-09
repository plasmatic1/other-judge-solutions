import sys
input = sys.stdin.readline

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

MSZ = 41
n, k = map(int, input().split())
seq = [(i, gcd(int(v), k)) for i, v in enumerate(input().split(), start=1)]
seq.sort(reverse=True)
seq = [1] + seq
MSZ = min(MSZ, n + 1)

dp = [[1] * MSZ for _ in range(n + 1)]
par = [[-1] * MSZ for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(1, MSZ):
        dp[i][j] = dp[i - 1][j]
        par[i][j] = (i - 1, j)
        
        alt = gcd(dp[i - 1][j - 1] * seq[i][1], k)
        if alt > dp[i][j]:
            dp[i][j] = alt
            par[i][j] = (i - 1, j - 1)
        # print(f'i={i}, j={j}, dpv={dp[i][j]}')

best = 1000000000
besti = -1
for i in range(1, n + 1):
    for j in range(1, MSZ):
        if dp[i][j] == k:
            best = min(best, j)
            besti = i
if best == 1000000000:
    print(-1)
else:
    print(best)

    # backtrack
    ans = []
    curi = besti
    curj = best
    while curi > 0 and curj > 0:
        pari, parj = par[curi][curj]
        if parj < curj:
            ans.append(seq[curi][0])
        curi = pari
        curj = parj
    ans.sort()
    print(' '.join(map(str, ans)))
