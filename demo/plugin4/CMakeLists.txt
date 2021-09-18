cmake_minimum_required(VERSION 3.10)

project(plugin4)

include_directories(../../include)

add_library(plugin4 SHARED plugin4.cpp )