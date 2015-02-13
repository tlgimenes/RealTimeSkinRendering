# Minimum cmake version
cmake_minimum_required(VERSION 3.1)

set(LIB_NAME skinengine)

# C Flags
set(C_FLAGS -std=c++11)

# Sources
set(SRC 
    mesh.cpp 
    mesh_loader_obj.cpp 
    mesh_loader_off.cpp 
    mesh_factory.cpp
    mesh_gl.cpp
    texture.cpp
    texture_loader_jpeg.cpp
    texture_loader_ppm.cpp
    texture_factory.cpp
    triangle.cpp
    parser.cpp
    camera.cpp
    shader.cpp 
    shader_phong.cpp
    shader_realskin.cpp
    )
set(INC ${CMAKE_SOURCE_DIR}/include)

# Compiler flags
add_definitions(${C_FLAGS})

# Internal header files
include_directories(${INC})

# Link internal files
add_library(${LIB_NAME} ${SRC})
