#include <iostream>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "romalcpp_examples_ros2_msgs/msg/hello_world.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalSubscriber : public rclcpp::Node {
 public:
  MinimalSubscriber() : Node("minimal_subscriber") {
    subscription_ = create_subscription<romalcpp_examples_ros2_msgs::msg::HelloWorld>(
        "topic", 10, [this](const romalcpp_examples_ros2_msgs::msg::HelloWorld& msg) {
          RCLCPP_INFO(get_logger(), "I heard: '%s'", msg.message_deprecated.c_str());
          //RCLCPP_INFO(get_logger(), "I heard: '%d'", msg.fooint);
        });
  }

 private:
  rclcpp::Subscription<romalcpp_examples_ros2_msgs::msg::HelloWorld>::SharedPtr subscription_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
