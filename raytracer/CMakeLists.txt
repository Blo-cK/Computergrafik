cmake_minimum_required (VERSION 3.9)
project (raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

add_executable(raytracer raytracer.cc math_test math_test.cc math.cc geometry_test.cc geometry.cc geometry_test
        geometry.h
        geometry.tcc
        color.h
)
target_link_libraries(raytracer gtest gtest_main)

