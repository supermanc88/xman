cmake_minimum_required(VERSION 3.10)

project(plugin3)

include_directories(../../include)

add_library(plugin3 SHARED plugin3.cpp)