#!/bin/bash
g++ -O2 -DLOCAL cheating-detection.cpp
./a.out < in > out

echo "Wrong Lines (target <= 14)"
diff out exp | grep "^<" | wc -l
