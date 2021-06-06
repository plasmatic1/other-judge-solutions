#!/bin/bash
echo "Compiling..."
g++ $(cat ~/dbflag) $1 -o prog
echo "Running..."
./prog < $2 > out
echo "Output:"
cat out

