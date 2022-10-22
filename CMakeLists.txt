cmake_minimum_required(VERSION 3.20)

project(OpenGl)

set(CMAKE_CXX_STANDARD 14)

include_directories(OpenGL
        Dependencies/GLFW/include
        Dependencies/glew-2.1.0/include
        OpenGL/src/effectTasks
        OpenGL/src/export
        OpenGL/src/glElement
        OpenGL/src/vendor)

file(GLOB_RECURSE src OpenGL/src/*.cpp)

set(forAdd
        OpenGL/src/effectTasks/OG6Coordinate2.cpp
        OpenGL/src/effectTasks/OG7Camera2.cpp
        )

add_executable(OpenGL OpenGL/src/Application.cpp ${forAdd} ${src})