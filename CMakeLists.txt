cmake_minimum_required(VERSION 3.27)
project(learnOpenGL)

set(CMAKE_CXX_STANDARD 20)
include_directories(./Dependencies/include)
link_directories(./Dependencies/lib)

add_executable(learnOpenGL main.cpp
        glad.c
        shader.h
)
target_link_libraries(learnOpenGL glfw3)
