cmake_minimum_required(VERSION 3.16)
project(simple_cpp_demo)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件目录，让编译器找到include里的.h
include_directories(include)

# 定义编译选项：是否开启调试打印，默认OFF
option(PRINT_DEBUG "enable debug print" OFF)

# 如果开启这个选项，就定义宏 PRINT_DEBUG
if(PRINT_DEBUG)
    add_definitions(-DPRINT_DEBUG)
endif()

# 指定要编译的所有cpp源文件
add_executable(demo src/main.cpp src/math_func.cpp)
