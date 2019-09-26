cmake_minimum_required(VERSION 3.10)
project(lexer)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
flex_target(flex lexer.lex ${CMAKE_CURRENT_BINARY_DIR}/lex.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(lexer main.cpp ${FLEX_flex_OUTPUTS})
