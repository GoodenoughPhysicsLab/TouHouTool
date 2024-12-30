cmake_minimum_required(VERSION 3.15)

project(thtool LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/nologo /Zc:preprocessor /utf-8 /DNOMINMAX /bigobj)
else()
    add_compile_options(-Wall -Wextra -Wno-parentheses)
    if (WIN32)
        add_compile_options(-finput-charset=utf-8 -fexec-charset=utf-8)
    endif()
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/../dist)
    file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/../dist)
endif()
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/../thtool.egg-info)
# remove thtool/*.pyd
file(GLOB thtool-pyds ${CMAKE_SOURCE_DIR}/../thtool/*.pyd)
foreach(thtool-pyd IN LISTS thtool-pyds)
    file(REMOVE ${thtool-pyd})
endforeach()

add_subdirectory(pybind11)
add_subdirectory(window)
add_subdirectory(objects)
