cmake_minimum_required(VERSION 3.10)

project(plugin2)

include_directories(../../include)

add_library(plugin2 SHARED plugin2.cpp)
