#!/bin/bash

echo "building"
gcc -lcunit unit_test.c msg.c buffer.c -o unit_test

echo "running"
./unit_test