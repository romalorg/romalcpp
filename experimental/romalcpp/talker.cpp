// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "romalcpp_examples_ros2_msgs/msg/hello_world.hpp"
#include "std_msgs/msg/string.hpp"

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */

class MinimalPublisher : public rclcpp::Node {
 public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0) {
    declare_parameter("callback_period_ms", 500);
    auto callback_period_ms = get_parameter("callback_period_ms").as_int();

    publisher_ = create_publisher<romalcpp_examples_ros2_msgs::msg::HelloWorld>("topic", 10);
    auto timer_callback = [this]() -> void {
      auto message = romalcpp_examples_ros2_msgs::msg::HelloWorld();
      message.message = "Hello, world! " + std::to_string(count_++);
      RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.message.c_str());
      publisher_->publish(message);
    };
    timer_ = create_wall_timer(std::chrono::milliseconds(callback_period_ms), timer_callback);
  }

 private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<romalcpp_examples_ros2_msgs::msg::HelloWorld>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}