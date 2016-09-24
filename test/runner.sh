#!/bin/bash

bin=$1
suite=$2

find $2 -type f \
  | grep -v out$   \
  | xargs -n1 -I{} echo "cat {} | $bin | diff -u {}.out -" \
  | bash

