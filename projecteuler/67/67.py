with open('triangle.txt') as f:
    s = f.read()

g = [list(map(int, line.split())) for line in s.split('\n')]

n = len(g)
dp = [[-1] * n for _ in range(n)]

def rec(row, col):
    if row == n: return 0
    if dp[row][col] != -1: return dp[row][col]
    dp[row][col] = max(rec(row + 1, col), rec(row + 1, col + 1)) + g[row][col]
    return dp[row][col]

print(rec(0, 0))
