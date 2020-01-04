#!/bin/bash

make clean

make

for algorithm in "aut" "bfs01" "order_deg_bfs" "dp";
do
  LIMIT="1000"
  if [ "${algorithm}" == "dp" ]
  then
    LIMIT="500"
  fi
  for function in "sturdy" "swm" "msw" "mfw";
  do
    echo "Running ./sturdy_tester ${algorithm} ${function} 1 ${LIMIT}"
    ./sturdy_tester ${algorithm} ${function} 1 ${LIMIT} > testing/tmp.out
    DIFF=$(diff -q testing/tmp.out testing/${function}1-${LIMIT}.txt)
    if [ "$DIFF" != "" ]
    then
      echo Error
    else
      echo Good
    fi
  done
done

rm testing/tmp.out
make clean

