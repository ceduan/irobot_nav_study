#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_msgs/msg/string.hpp>
#include <sstream>

class StateMonitorNode : public rclcpp::Node
{
public:
  StateMonitorNode() : Node("state_monitor_node")
  {
    // 订阅安全速度话题
    sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel_safe",
      10,
      std::bind(&StateMonitorNode::vel_callback, this, std::placeholders::_1)
    );
    // 发布机器人状态字符串
    pub_ = this->create_publisher<std_msgs::msg::String>("/robot_state", 10);
    RCLCPP_INFO(this->get_logger(), "State Monitor Node 启动成功");
  }

private:
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;

  void vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    std_msgs::msg::String state_msg;
    std::stringstream ss;

    // 判断状态：速度全0=急停，否则正常运行
    bool is_stop = (msg->linear.x == 0.0 && msg->angular.z == 0.0);
    if(is_stop)
    {
      ss << "【急停状态】";
    }
    else
    {
      ss << "【正常运行】";
    }
    ss << " 线速度x:" << msg->linear.x << " 角速度z:" << msg->angular.z;
    state_msg.data = ss.str();

    pub_->publish(state_msg);
    RCLCPP_INFO(this->get_logger(), "%s", state_msg.data.c_str());
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StateMonitorNode>());
  rclcpp::shutdown();
  return 0;
}
