# ./bobs-fighting-with-monsters.yml
n, k = map(int, input().split())
n -= k * (n // k)
ans = n
for i in range(10):
    ans = min(ans, n)
    n = abs(n - k)

print(ans)
