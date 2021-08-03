cmake_minimum_required(VERSION 3.19)
project(the_game_of_polymorphism)

set(CMAKE_CXX_STANDARD 14)

add_executable(the_game_of_polymorphism main.cpp Weapon.h Knife.h Knife.cpp DragonSword.h DragonSword.cpp Hero.h Hero.cpp Monster.h Monster.cpp)