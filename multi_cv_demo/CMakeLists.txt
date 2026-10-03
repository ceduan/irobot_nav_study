cmake_minimum_required(VERSION 3.10)
project(multi_cv_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 告诉cmake：头文件去include文件夹找
include_directories(include)

# 寻找OpenCV库
find_package(OpenCV REQUIRED)

# 编译两个cpp文件，生成名为demo的可执行程序
add_executable(demo src/main.cpp src/image_proc.cpp)

# 链接OpenCV库
target_link_libraries(demo ${OpenCV_LIBS})
