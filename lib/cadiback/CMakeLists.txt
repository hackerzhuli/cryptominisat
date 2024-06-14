cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS -std=gnu++17)

add_library(cadiback STATIC cadiback.cpp)

add_subdirectory(../cadical ../cadical)

target_include_directories(cadiback PUBLIC ../cadical/src)