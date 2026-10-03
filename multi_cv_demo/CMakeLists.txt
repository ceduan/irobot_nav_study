cmake_minimum_required(VERSION 3.10)

# 项目名
project(multi_cv_demo)

# ==========指定C++版本，开启编译警告==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

# ==========定义编译宏，控制是否保存图片==========
option(SAVE_OUTPUT_IMAGE "Enable save processed image" ON)
if(SAVE_OUTPUT_IMAGE)
    add_definitions(-DSAVE_OUTPUT_IMAGE)
endif()

# 寻找OpenCV
find_package(OpenCV REQUIRED)

# 源码文件，【先创建可执行目标】
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/image_proc.cpp
)

# 【必须放在add_executable之后！】现代CMake头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

# 链接库
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
)
