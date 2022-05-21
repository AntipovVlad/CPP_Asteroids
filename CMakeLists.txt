cmake_minimum_required(VERSION 3.22)
project(Asteroids)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/StandardProjectSettings.cmake)
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_20)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

find_file(Asteroids Fonts/arial.ttf)

add_executable(
        Asteroids
        main.cpp
        View/main_funcs.cpp View/main_funcs.h
        View/main_screen_out.cpp View/main_screen_out.h
        Objects/Ship.cpp Objects/Ship.h
        Objects/BaseObject.cpp Objects/BaseObject.h
        Objects/Asteroid.cpp Objects/Asteroid.h
        Objects/Bullet.cpp Objects/Bullet.h)

target_link_libraries(Asteroids sfml-graphics sfml-audio)

enable_testing()

add_subdirectory(Doctest)
add_subdirectory(Testing)
