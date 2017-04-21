cmake_minimum_required(VERSION 3.5.1)
project(DE_DPS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

set(SOURCE_FILES main.cpp Vector.h MDE.h Random.h Constraints.h FunctionBase.h CEC_2006.h CEC_2006_C_Functions.h)
add_executable(DE_DPS ${SOURCE_FILES})