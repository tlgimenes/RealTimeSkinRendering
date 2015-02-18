# Minimum cmake version
cmake_minimum_required(VERSION 3.1)

set(LIB_NAME skinengine)

# Internal files
set(INC ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/inc)
set(C_FLAGS -std=c++11)
set(SRC parser.cpp
        program_phong.cpp
        program_realskin.cpp
        )

# Compiler flags
add_definitions(${C_FLAGS})

# Internal header files
include_directories(${INC})

add_library(${LIB_NAME} ${SRC})
