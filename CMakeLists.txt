cmake_minimum_required(VERSION 3.27.1)

project(thtool)

file(GLOB SRC_FILES
	"${PROJECT_SOURCE_DIR}/src/*.h"
	"${PROJECT_SOURCE_DIR}/src/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.hh"
	"${PROJECT_SOURCE_DIR}/src/*.ixx"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.cc"
	"${PROJECT_SOURCE_DIR}/src/mouse/*.ixx"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

add_compile_options(/GR-)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)