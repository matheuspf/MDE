cmake_minimum_required(VERSION 3.5.1)
project(DE_DPS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

set(SOURCE_FILES main.cpp Vector.h MDE.h)
add_executable(DE_DPS ${SOURCE_FILES})