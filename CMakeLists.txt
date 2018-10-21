cmake_minimum_required(VERSION 3.12)
project(mag_dist)

set(CMAKE_CXX_STANDARD 14)

set(
    incidence_matrix

        incidence_matrix/incidence_matrix.hpp
        incidence_matrix/incidence_matrix.cpp
)

add_executable(
    mag_dist
    main.cpp
    ${incidence_matrix}
)