cmake_minimum_required(VERSION 3.24)
project(DS C)

set(CMAKE_C_STANDARD 11)

add_executable(DS src/queue.h src/queue.c test/test_queue.c)
