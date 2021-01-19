# bob-buying-gifts.yml
n, t = map(int, input().split())
ans = 0
for i in range(n):
    c, v = map(int, input().split())
    if c <= t and v > ans:
        ans = v
print(ans)
