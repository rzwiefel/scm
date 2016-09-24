#!/bin/bash

bin=$1

find suite -type f \
  | grep -v out$   \
  | xargs -n1 -I{} echo "cat {} | $bin | diff -u {}.out -" \
  | bash

