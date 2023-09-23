cmake_minimum_required(VERSION 3.17)
project(Inheritance)

set(CMAKE_CXX_STANDARD 17)

add_executable(Inheritance main.cpp Banana.cpp Banana.h Chicken.cpp Chicken.h Cart.cpp Cart.h Item.cpp Item.h)