cmake_minimum_required(VERSION 3.31)
set(PROJECT_NAME testcpp)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 26)

add_executable(${PROJECT_NAME} main.cpp
        renderer/ShaderProgram.cpp
        renderer/ShaderProgram.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)