project(virtual)

cmake_minimum_required(VERSION 3.1)

add_library(base STATIC base.cc)
#add_executable(base base.cc)
add_subdirectory(child)

