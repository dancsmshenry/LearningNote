cmake_minimum_required(VERSION 3.19)
project(namespace_use)

set(CMAKE_CXX_STANDARD 14)

add_executable(namespace_use main.cpp game1.h game1.cpp game2.h game2.cpp)