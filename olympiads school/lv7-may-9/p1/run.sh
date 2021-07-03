#!/bin/bash

src=$2
[ -z $src ] && src=main

case $1 in 
    1) flag="$(cat ../../cco/flag)";;
    *) flag="-O0";;
esac

echo Flags: $flag
echo $src: $src
g++ $src.cpp -o main -DLOCAL $flag || exit

for ((t=0;;t++)); do
    if [ -f $t.in ]; then

        echo "Case $t"
        echo "-- Input --"
        cat $t.in
        echo 

        ./main < $t.in > out
        echo "-- Output --"
        cat out
        echo
    else
        break
    fi
done
