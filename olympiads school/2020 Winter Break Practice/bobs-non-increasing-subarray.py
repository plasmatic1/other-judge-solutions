# ./bobs-non-increasing-subarray.yml
N = int(input())
a = list(map(int, input().split()))
ans = 0
i = 0
while i < N:
    j = i
    while j+1 < N and a[j+1] <= a[j]:
        j += 1
    ans = max(ans, j-i+1)
    i = j+1
print(ans)
