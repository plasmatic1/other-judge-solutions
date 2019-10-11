#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the maxSubarray function below.
def maxSubarray(arr):
    n = len(arr)

    pfx = [0] + [i for i in arr]
    for i in range(1, n + 1):
        pfx[i] += pfx[i - 1]
    
    bestl = 0
    best = -1000000000

    for i in range(1, n + 1):
        best = max(best, pfx[i] - bestl)
        bestl = min(bestl, pfx[i])
    
    print(pfx, bestl, best)
    
    sumv = sum(map(lambda v: 0 if v < 0 else v, arr))
    
    return (best, max(arr) if sumv == 0 else sumv)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        arr = list(map(int, input().rstrip().split()))

        result = maxSubarray(arr)

        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')

    fptr.close()
