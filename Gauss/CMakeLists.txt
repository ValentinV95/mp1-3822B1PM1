cmake_minimum_required(VERSION 3.24)
project(Gauss)

set(CMAKE_CXX_STANDARD 17)

add_executable(Gauss main.cpp matrix.h vector.h funcs.h funcs.cpp funcs.cpp matrix.cpp matrix.cpp vector.cpp vector.cpp)
