cmake_minimum_required(VERSION 3.5.1)
project (examples)

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

include_directories(${PARENT_DIR}/include)

file(GLOB CEC_SRC_FILES CEC2006/*.cpp)


set(CXXFLAGS "-std=c++14 -O3")



add_executable(CEC2006Example ${CEC_SRC_FILES} CEC2006Example.cpp)

add_executable(FunctionsExample ${CEC_SRC_FILES} FunctionsExample.cpp)