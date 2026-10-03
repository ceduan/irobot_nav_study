# cmd_vel_guard
IRobot算法组 导航方向 ROS2速度安全保护模块
> 适配西电电赛机器人导航，实现速度限幅 + 超时急停功能

## 功能说明
1. 订阅 `/cmd_vel` 原始速度指令
2. 对线速度、角速度做阈值限幅，防止机器人超速
3. 消息超时检测：长时间无指令自动置零，触发急停保护
4. 发布安全后的速度话题 `/cmd_vel_safe`
5. 状态节点实时打印当前速度与急停状态

## 运行环境
- Ubuntu 22.04
- ROS2 Humble
- C++

## 编译与启动
```bash
colcon build --packages-select cmd_vel_guard
source install/setup.bash
ros2 launch cmd_vel_guard robot_guard.launch.py
