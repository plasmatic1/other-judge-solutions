#!/bin/bash
g++ -O2 -DLOCAL cheating-detection.cpp
./a.out < ts2_input.txt > out

echo "Wrong Lines (target <= 14)"
diff out ts2_output.txt | grep "^<" | wc -l
