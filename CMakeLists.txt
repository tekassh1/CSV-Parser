cmake_minimum_required(VERSION 2.8)
project(YadroCSV)

file(GLOB SOURCES "src/*.cpp")
set(HEADERS include)

add_definitions(-Wall -O2)

include_directories(${HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES})