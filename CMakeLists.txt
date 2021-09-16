cmake_minimum_required(VERSION 3.10)

project(xman)

set(CMAKE_CXX_STANDARD 11)

# 调试选项
#set(CMAKE_CXX_FLAGS -O0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# 获取所有源码文件
file(GLOB SRC_LISTS ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
message(${SRC_LISTS})

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
message(${EXECUTABLE_OUTPUT_PATH})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/plugin)
message(${LIBRARY_OUTPUT_PATH})

# 测试unix
#add_definitions(-D__GNUC__)

add_executable(${PROJECT_NAME} ${SRC_LISTS})

message(${CMAKE_SYSTEM_NAME})
# 如果是Linux系统，需要在编译时加入dl
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message("platform: Linux")
    target_link_libraries(${PROJECT_NAME} -ldl)
endif()



add_subdirectory(demo/plugin1)
add_subdirectory(demo/plugin2)
add_subdirectory(demo/plugin3)
