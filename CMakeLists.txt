cmake_minimum_required(VERSION 3.21)
project(Asteroids)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_file(Asteroids Fonts/arial.ttf)

set(CMAKE_CXX_STANDARD 14)

add_executable(Asteroids main.cpp)

target_link_libraries(Asteroids sfml-graphics sfml-audio)
