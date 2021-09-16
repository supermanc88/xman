cmake_minimum_required(VERSION 3.10)

project(plugin1)

include_directories(../../include)

add_library(plugin1 SHARED plugin1.cpp)