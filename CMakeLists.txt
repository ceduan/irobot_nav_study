cmake_minimum_required(VERSION 3.10)
project(nav_opencv_demo)
# 查找OpenCV库
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV Version: ${OpenCV_VERSION}")
# 生成可执行程序demo
add_executable(demo test_opencv.cpp)
# 链接OpenCV库
target_link_libraries(demo ${OpenCV_LIBS})

add_executable(edge_detect edge_detect.cpp)
target_link_libraries(edge_detect ${OpenCV_LIBS})
