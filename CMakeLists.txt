cmake_minimum_required(VERSION 3.31)
set(PROJECT_NAME testcpp)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 26)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)