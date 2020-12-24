cmake_minimum_required(VERSION 3.17)
project(computerGraphicsPractice)

set(CMAKE_CXX_STANDARD 14)

add_executable(computerGraphicsPractice main.cpp Convex.cpp Convex.h CameraTransform.cpp CameraTransform.h)
target_link_libraries(computerGraphicsPractice -lglut -lGL -lGLU)