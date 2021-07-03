#!/bin/bash

case $1 in 
    1) flag="$(cat ../../cco/flag)";;
    *) flag="-O0";;
esac

echo Flags: $flag
g++ main.cpp -o main -DLOCAL $flag || exit

for ((t=0;;t++)); do
    if [ -f $t.in ]; then

        echo "Case $t"
        echo "-- Input --"
        cat $t.in
        echo 

        ./main < $t.in > out-$t
        echo "-- Output --"
        cat out-$t
        echo
    else
        break
    fi
done
