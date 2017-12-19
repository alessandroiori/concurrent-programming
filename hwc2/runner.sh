#!/usr/bin/env bash

echo "building"
gcc -lcunit ./test_driver.c \
            ./accepter/*.c ./accepter/test/*.c \
            ./dispatcher/*.c ./dispatcher/test/*.c \
            ./provider/*.c ./provider/test/*.c \
            ./reader/*.c ./reader/test/*.c \
            ./lib/buffer/*.c ./lib/buffer/test/*.c \
            ./lib/buffer_concurrent/*.c ./lib/buffer_concurrent/test/*.c \
            ./lib/hwc2list/*.c ./lib/list_concurrent/*.c \
            ./lib/monitor_buffer/*.c ./lib/msg/*.c ./lib/poison_pill/*.c \
            -o test_runner

echo "running"
./test_runner