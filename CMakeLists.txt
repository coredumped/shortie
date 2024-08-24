cmake_minimum_required(VERSION 3.26)

project("shortie" VERSION 0.0.1)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)


add_executable("shortie" src/main.cpp src/shortie.cpp)
