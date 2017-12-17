#!/usr/bin/env bash

echo "building"
gcc -lcunit ./*.c ./hwc1/*.c ./hwc2list/*.c ./test/*.c -o test_runner

echo "running"
./test_runner