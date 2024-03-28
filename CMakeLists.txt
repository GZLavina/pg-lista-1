cmake_minimum_required(VERSION 3.27)
project(learnOpenGL)

set(CMAKE_CXX_STANDARD 20)
set(USER_HOME_DIRECTORY $ENV{USERPROFILE})
message(STATUS "User Home Directory: ${USER_HOME_DIRECTORY}")

include_directories(${USER_HOME_DIRECTORY}/OpenGL/include)
link_directories(${USER_HOME_DIRECTORY}/OpenGL/Libs)

add_executable(learnOpenGL main.cpp
        glad.c
        shader.h
        shader.cpp
)
target_link_libraries(learnOpenGL glfw3)
