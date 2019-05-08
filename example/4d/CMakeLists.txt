cmake_minimum_required(VERSION 2.8)

project(d4)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    d4
    4poly.cpp
)

target_include_directories(
    d4
    PUBLIC
    src
)