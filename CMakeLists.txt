cmake_minimum_required(VERSION 3.24)
project(2_ALGOS_Aktien)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(2_ALGOS_Aktien
        hashtable.cpp
        README.md header/hashtable.h)
