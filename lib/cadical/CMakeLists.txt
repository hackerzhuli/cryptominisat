cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

FILE(GLOB MyCSources  src/*.cpp)
add_library(cadical STATIC ${MyCSources})

