cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project (table-test)

set (CMAKE_CXX_STANDARD 11)

include_directories (table)

ADD_EXECUTABLE (table-test main.cpp)
