cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES examples/firstthread.c examples/args_threads.c examples/proces/exec_fork.c hwc1/msg.c hwc1/msg.h hwc1/msg.c hwc1/msg.h hwc1/buffer.c hwc1/buffer.h hwc1/functions.c hwc1/functions.h)
add_executable(untitled ${SOURCE_FILES})