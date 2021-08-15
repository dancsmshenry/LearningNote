cmake_minimum_required(VERSION 3.19)
project(extern_c)

set(CMAKE_CXX_STANDARD 14)

add_executable(extern_c main.cpp test.c)