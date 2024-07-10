cmake_minimum_required(VERSION 3.10)

project(thtool)

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.cc"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

if(THTOOL_CLOSE_COLOR_PRINT)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE THTOOL_CLOSE_COLOR_PRINT)
endif()