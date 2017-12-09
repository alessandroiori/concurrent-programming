#!/usr/bin/env bash

echo "building"
gcc -lcunit ./test_driver.c ./hwc1/*.c ./test/*.c -o test_runner

echo "running"
./test_runner