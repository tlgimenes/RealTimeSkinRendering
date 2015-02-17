# Minimum cmake version
cmake_minimum_required(VERSION 3.1)

# Project name
project(RealTimeSkinRendering)

# Internal files
set(SRC main.cpp)
set(INC ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/inc)
set(SUB_DIRS ${CMAKE_SOURCE_DIR}/src)
set(C_FLAGS -std=c++11)

# Compiler flags
add_definitions(${C_FLAGS})

# Internal header files
include_directories(${INC})
subdirs(${SUB_DIRS})

# Include FindOBJ.cmake in the path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# Required external packages
find_package(OpenGL REQUIRED)
find_package(GLUT   REQUIRED)
find_package(GLEW   REQUIRED)
find_package(JPEG   REQUIRED)
find_package(OBJ    REQUIRED)

# Link internal files
add_executable(skinrenderer ${SRC})

# Include OpenGL and GLUT folders
include_directories(${OPENGL_INCLUDE_DIRS}  
                    ${GLUT_INCLUDE_DIRS}
                    ${GLEW_INCLUDE_DIRS})


# Link necessary libraries
target_link_libraries(skinrenderer
                     ${OPENGL_LIBRARIES} 
                     ${GLUT_LIBRARY}
                     ${GLEW_LIBRARIES}
                     ${LIBJPEG_LIBRARY}
                     ${LIBOBJ_LIBRARY}
                     )

target_link_libraries(skinrenderer 
                      skinengine)
