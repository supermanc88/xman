cmake_minimum_required(VERSION 3.10)

project(xman)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# 获取所有源码文件
file(GLOB SRC_LISTS ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
message(${SRC_LISTS})

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
message(${EXECUTABLE_OUTPUT_PATH})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/lib)
message(${LIBRARY_OUTPUT_PATH})

# 测试unix
add_definitions(-D__GNUC__)

add_executable(${PROJECT_NAME} ${SRC_LISTS})