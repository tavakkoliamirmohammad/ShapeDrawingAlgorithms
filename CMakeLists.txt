cmake_minimum_required(VERSION 3.17)
project(computerGraphicsPractice)

set(CMAKE_CXX_STANDARD 14)

add_executable(computerGraphicsPractice main.cpp lineGeneration.cpp Circles.cpp Circles.h Ellipse.cpp Ellipse.h Parabola.cpp Parabola.h Cycloid.cpp Cycloid.h PingPong.cpp PingPong.h)
target_link_libraries(computerGraphicsPractice -lglut -lGL -lGLU)