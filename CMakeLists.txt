cmake_minimum_required(VERSION 3.10)

project(LogicInterp)

set(CMAKE_CXX_STANDARD 23)

add_executable(LogicInterp src/main.cpp src/lexer.cpp src/repl.cpp)
