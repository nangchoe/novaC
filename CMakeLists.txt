cmake_minimum_required(VERSION 3.10)

project(novac)

set(CMAKE_CXX_STANDARD 17)

add_executable(novac

compiler/main.cpp
compiler/lexer.cpp
compiler/parser.cpp

)