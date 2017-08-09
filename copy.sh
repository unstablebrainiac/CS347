#!/bin/bash

start=`date +%s`

filename=$1
num=$2

mkdir files
for i in $(seq 1 $num)
do
    cp $filename ./files/$filename$i
done

end=`date +%s`

runtime=$((end-start))
echo $runtime
