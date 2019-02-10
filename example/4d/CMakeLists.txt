cmake_minimum_required(VERSION 2.8)

project(d4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(skeleton)

add_executable(
    d4
    4poly.cpp
)

target_include_directories(
    skeleton
    PUBLIC
    skeleton/src
)

target_link_libraries(d4 skeleton)


target_include_directories(
    d4
    PUBLIC
    src
)