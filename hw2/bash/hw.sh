#!/bin/bash

echo "1. Loop for even numbers:"
for i in `seq 100 2 1000`
do
    echo $i
done

echo "-----"

echo "2. Printing elements of array:"

cities=(Lissabon Madrid Paris Berlin London Rome Brussels Amsterdam Warsaw Kiev Minsk Moscow)
for each in "${cities[@]}" 
do
    echo $each
done

echo "-----"

echo "3. Float operations (sum):"
A=100
B=0.5
echo "($A + $B)" | bc

echo "-----"

echo "4. Linux folder:"
if [ -d "./Linux" ]
then
    echo "course"
else
    echo "very easy"
    mkdir "./Linux"
fi
