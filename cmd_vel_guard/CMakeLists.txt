cmake_minimum_required(VERSION 3.8)
project(cmd_vel_guard)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 找到依赖包，对应package.xml里面写的依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# ========== 节点1：速度安全防护节点 ==========
add_executable(velocity_safety_node src/velocity_safety_node.cpp)
ament_target_dependencies(velocity_safety_node rclcpp geometry_msgs std_msgs)

# ========== 节点2：状态监控节点 ==========
add_executable(state_monitor_node src/state_monitor_node.cpp)
ament_target_dependencies(state_monitor_node rclcpp geometry_msgs std_msgs)

# 安装：编译出来的可执行文件、launch文件夹，安装到install目录
install(TARGETS
  velocity_safety_node
  state_monitor_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
