#!/bin/bash

echo "building"
gcc -lcunit test.c functions.c msg.c buffer.c -o test

echo "running"
./test