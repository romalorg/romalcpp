#pragma once

#include <iostream>
#include <memory>

#include "romalcpp/node.h"
#include "romalcpp/publisher.h"
#include "romalcpp/timer.h"
#include "romalcpp_examples_ros2_msgs/msg/hello_world.hpp"

namespace romalcpp::examples {

template <class NodeImpl>
class TalkerNode {
 public:
  static constexpr const char* kTopic = "/topic";
  static constexpr int kPublisherQueueSize = 10;
  static constexpr int kCallbackPeriodMs = 500;

  explicit TalkerNode(std::shared_ptr<romalcpp::Node<NodeImpl>> node)
      : node_{std::move(node)},
        publisher_{node_->template createPublisher<romalcpp_examples_ros2_msgs::msg::HelloWorld>(
            kTopic, kPublisherQueueSize)},
        timer_{node_->template createTimer(std::chrono::milliseconds(kCallbackPeriodMs),
                                           [this]() { this->timerCallback(); })} {}

  void timerCallback() {
    romalcpp_examples_ros2_msgs::msg::HelloWorld msg;
    msg.message = "Hello, world! " + std::to_string(count_++);
    std::cout << "Publishing: " << msg.message << std::endl;
    publisher_->publish(msg);
  }

 private:
  std::shared_ptr<romalcpp::Node<NodeImpl>> node_;
  std::shared_ptr<romalcpp::Publisher<romalcpp_examples_ros2_msgs::msg::HelloWorld>> publisher_;
  std::shared_ptr<romalcpp::Timer> timer_;
  size_t count_ = 0U;
};

}  // namespace romalcpp::examples
