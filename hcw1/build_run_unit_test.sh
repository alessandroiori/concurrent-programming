#!/bin/bash

echo "building"
gcc -lcunit hwc1_unit_test.c msg.c buffer.c -o hwc1_unit_test

echo "running"
./hwc1_unit_test