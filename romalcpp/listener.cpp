#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace romalcpp::examples {

class MinimalSubscriber : public rclcpp::Node {
 public:
  MinimalSubscriber() : Node("minimal_subscriber") {
    subscription_ = create_subscription<std_msgs::msg::String>(
        "topic", 10, [this](const std_msgs::msg::String& msg) {
          RCLCPP_INFO(get_logger(), "I heard: '%s'", msg.data.c_str());
        });
  }

 private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

}  // namespace romalcpp::examples
