cmake_minimum_required(VERSION 2.8)

project(skeleton)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tools/arageli)

add_library(skeleton SHARED
    src/ddm.hpp
    src/ddmio.hpp
    src/skeleton.cpp
    src/skeleton.h
#    src/main.cpp
)

target_include_directories( arageli PUBLIC
    src
    )

target_include_directories(skeleton
    PUBLIC src
    )

target_link_libraries(skeleton arageli)

target_include_directories(
    arageli PRIVATE
    tools/arageli/src
)

