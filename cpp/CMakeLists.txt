cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")
project(cpp)
add_subdirectory(pybind11)

add_subdirectory(prints)
add_subdirectory(window)