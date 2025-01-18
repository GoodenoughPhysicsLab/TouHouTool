cmake_minimum_required(VERSION 3.15)

project(auto_th10 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/nologo /Zc:preprocessor /utf-8 /DNOMINMAX /bigobj)
else()
    add_compile_options(-Wall -Wextra -Wno-parentheses)
    if (WIN32)
        add_compile_options(-finput-charset=utf-8 -fexec-charset=utf-8)
    endif()
endif()

# remove dist directory
if (EXISTS ${CMAKE_SOURCE_DIR}/../dist)
    file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/../dist)
    message(STATUS "remove ${CMAKE_SOURCE_DIR}/../dist")
endif()
# remove auto_th10.egg-info
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/../auto_th10.egg-info)
message(STATUS "remove ${CMAKE_SOURCE_DIR}/../auto_th10.egg-info")
# remove auto_th10/*.pyd
file(GLOB auto_th10-pyds ${CMAKE_SOURCE_DIR}/../auto_th10/*.pyd)
foreach(auto_th10-pyd IN LISTS auto_th10-pyds)
    file(REMOVE ${auto_th10-pyd})
    message(STATUS "remove ${auto_th10-pyd}")
endforeach()

add_subdirectory(pybind11)

pybind11_add_module(${PROJECT_NAME} src/auto_th10.cc)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/../auto_th10)
