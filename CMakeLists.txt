cmake_minimum_required(VERSION 2.8)
project(YadroCSV)

set(SOURCES src/Main.cpp)
set(INCLUDE_LIST include)

add_definitions(-Wall -O2)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(INCLUDE)