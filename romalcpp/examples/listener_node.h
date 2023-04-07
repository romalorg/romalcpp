#pragma once

#include <iostream>
#include <memory>

#include "romalcpp/node.h"
#include "romalcpp/subscriber.h"
#include "romalcpp_examples_ros2_msgs/msg/hello_world.hpp"

namespace romalcpp::examples {

template <class NodeImpl>
class ListenerNode {
 public:
  static constexpr const char* kTopic = "/topic";
  static constexpr int kSubscriberQueueSize = 10;

  explicit ListenerNode(std::shared_ptr<romalcpp::Node<NodeImpl>> node)
      : node_{std::move(node)},
        subscriber_{node_->template createSubscriber<romalcpp_examples_ros2_msgs::msg::HelloWorld>(
            kTopic, kSubscriberQueueSize,
            [this](const romalcpp_examples_ros2_msgs::msg::HelloWorld& msg) {
              this->msgCallback(msg);
            })} {}

  void msgCallback(const romalcpp_examples_ros2_msgs::msg::HelloWorld& msg) {
    std::cout << "Received: " << msg.message << std::endl;
  };

 private:
  std::shared_ptr<romalcpp::Node<NodeImpl>> node_;
  std::shared_ptr<romalcpp::Subscriber<romalcpp_examples_ros2_msgs::msg::HelloWorld>> subscriber_;
};

}  // namespace romalcpp::examples
