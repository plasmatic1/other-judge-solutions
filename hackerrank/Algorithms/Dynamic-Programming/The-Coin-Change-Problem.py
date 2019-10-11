#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the getWays function below.
def getWays(n, c):
    m = len(c)
    c = list(sorted(c))

    dp = [[0] * (n + 1) for _ in range(m)]

    def rec(amt=0, cur=0):
        if amt > n:
            return 0
        elif amt == n:
            return 1
        elif dp[cur][amt]:
            return dp[cur][amt]
        
        tot = 0
        for i in range(cur, m):
            tot += rec(amt + c[i], i)
        
        dp[cur][amt] = tot
        return dp[cur][amt]
    
    return rec()

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    c = list(map(int, input().rstrip().split()))

    # Print the number of ways of making change for 'n' units using coins having the values given by 'c'

    ways = getWays(n, c)

    fptr.write(str(ways) + '\n')

    fptr.close()