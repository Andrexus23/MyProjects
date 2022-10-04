cmake_minimum_required(VERSION 3.23)
project(program_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(program1 main.cpp Client.h Client.cpp BufferManager.h BufferManager.cpp)
