#!/bin/bash
echo "Compiling..."
g++ -O2 $1 -o prog
echo "Running..."
./prog < $2 > out
echo "Output (in file out as well):"
cat out
