import sys
input=sys.stdin.readline
n=int(input())
a=list(map(int,input().split()))
dp=[1]*n
for i in xrange(1,n):
    for j in xrange(max(0,i-31),i):
        if j+a[j]<i:
            dp[i]=max(dp[i],dp[j]+1)
print max(dp)