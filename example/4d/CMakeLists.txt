cmake_minimum_required(VERSION 2.8)

project(poly4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(skeleton)

add_executable(
    poly4
    4poly.cpp
)

target_include_directories(
    skeleton
    PUBLIC
    skeleton/src
)

target_link_libraries(poly4 skeleton)


target_include_directories(
    poly4
    PUBLIC
    src
)