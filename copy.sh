#!/bin/bash

start=`date +%s`

filename=$1
num=$2

mkdir files
for i in $(seq 1 $num)
do
    cp $filename ./files/$filename$i
done

line=`lsof | grep "copy.sh" | head -1`
arr=($line)

end=`date +%s`
runtime=$((end-start))
echo Runtime: $runtime s
echo PID: ${arr[1]}
