#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <chrono>

using namespace std::chrono_literals;

class VelocitySafetyGuard : public rclcpp::Node
{
public:
  VelocitySafetyGuard() : Node("velocity_safety_node")
  {
    // ========== 读取ROS参数（作业硬性要求 Parameter） ==========
    this->declare_parameter<double>("max_linear", 0.5);
    this->declare_parameter<double>("max_angular", 1.0);
    max_linear_ = this->get_parameter("max_linear").as_double();
    max_angular_ = this->get_parameter("max_angular").as_double();

    // 订阅原始速度话题 /cmd_vel
    sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel",
      10,
      std::bind(&VelocitySafetyGuard::cmd_vel_callback, this, std::placeholders::_1)
    );

    // 发布处理后的安全速度话题 /cmd_vel_safe
    pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel_safe", 10);

    // 定时器：用来检测超时，50ms检查一次
    timer_ = this->create_wall_timer(
      50ms,
      std::bind(&VelocitySafetyGuard::timer_callback, this)
    );
    last_msg_time_ = this->now();
    RCLCPP_INFO(this->get_logger(), "Velocity Safety Guard 启动成功");
    RCLCPP_INFO(this->get_logger(), "max_linear: %.2f, max_angular: %.2f", max_linear_, max_angular_);
  }

private:
  double max_linear_;
  double max_angular_;
  rclcpp::Time last_msg_time_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  // 收到cmd_vel消息的回调函数
  void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    last_msg_time_ = this->now();
    geometry_msgs::msg::Twist safe_msg = *msg;

    // 限幅：线速度限制
    if (safe_msg.linear.x > max_linear_) safe_msg.linear.x = max_linear_;
    if (safe_msg.linear.x < -max_linear_) safe_msg.linear.x = -max_linear_;

    // 限幅：角速度限制
    if (safe_msg.angular.z > max_angular_) safe_msg.angular.z = max_angular_;
    if (safe_msg.angular.z < -max_angular_) safe_msg.angular.z = -max_angular_;

    pub_->publish(safe_msg);
  }

  // 定时器回调，超时判断
  void timer_callback()
  {
    auto now = this->now();
    auto duration = now - last_msg_time_;
    // 超过0.2s没有收到指令，输出0速度，急停
    if (duration.seconds() > 0.2)
    {
      geometry_msgs::msg::Twist stop_msg;
      stop_msg.linear.x = 0.0;
      stop_msg.angular.z = 0.0;
      pub_->publish(stop_msg);
    }
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelocitySafetyGuard>());
  rclcpp::shutdown();
  return 0;
}
