from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 节点1：速度安全防护节点，在这里设置参数
    velocity_guard_node = Node(
        package="cmd_vel_guard",
        executable="velocity_safety_node",
        name="velocity_safety_node",
        parameters=[
            {"max_linear": 0.6},
            {"max_angular": 1.2}
        ]
    )

    # 节点2：状态监控节点
    state_monitor_node = Node(
        package="cmd_vel_guard",
        executable="state_monitor_node",
        name="state_monitor_node"
    )

    # 把两个节点放进启动列表
    return LaunchDescription([
        velocity_guard_node,
        state_monitor_node
    ])
