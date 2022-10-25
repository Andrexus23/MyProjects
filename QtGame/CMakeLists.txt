cmake_minimum_required(VERSION 3.21)
project(Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(Game
        inc/cell.h
        inc/map.h
        src/cell.cpp
        src/main.cpp
        src/map.cpp)
