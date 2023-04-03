cmake_minimum_required(VERSION 3.14)
project(RingBuffer)

add_library(unity STATIC test/lib/Unity/src/unity.c)

include_directories(include)

add_executable(RingBuffer src/ring_buffer.c test/test.c)

target_link_libraries(RingBuffer unity)