# CMake minimum version requirement
cmake_minimum_required(VERSION 3.10)

# Project name
project(steeles)

# Set the C compiler (optional, CMake will detect it automatically)
# set(CMAKE_C_COMPILER gcc)

# Add custom target for preprocessing only
add_custom_target(preprocess
        COMMAND ${CMAKE_C_COMPILER} -E -o preprocess_output.i ${CMAKE_SOURCE_DIR}/src/main.c
        DEPENDS ${CMAKE_SOURCE_DIR}/src/main.c
)

# Set include directories for preprocessing
include_directories(${CMAKE_SOURCE_DIR}/src/assets)
include_directories(${CMAKE_SOURCE_DIR}/src/lib)