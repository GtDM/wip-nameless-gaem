cmake_minimum_required(VERSION 2.8.9)
project(wip-nameless-gaem)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -pedantic")
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} Box2D sfml-graphics sfml-window sfml-system)
