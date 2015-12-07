#!/bin/sh

for i in $(seq 0 1000)
do
#  echo $i
  ./simple_race
done

