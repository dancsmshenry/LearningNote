cmake_minimum_required(VERSION 3.19)
project(const_test_in_c C)

set(CMAKE_C_STANDARD 99)

add_executable(const_test_in_c main.c test.c)