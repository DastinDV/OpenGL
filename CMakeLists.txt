cmake_minimum_required(VERSION 3.16)
project(OpenGLLearn)

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)
set(BIN_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/bin)

#GLFW
add_subdirectory(${LIB_DIR}/glfw ${BIN_LIB_DIR}/glfw)

#GLAD
add_library(GLAD ${LIB_DIR}/glad/src/glad.c)
target_include_directories(GLAD PUBLIC ${LIB_DIR}/glad/include)

#EXECUTABLE
add_executable(OpenGLLearn main.cxx)
target_link_libraries(OpenGLLearn glfw GLAD)