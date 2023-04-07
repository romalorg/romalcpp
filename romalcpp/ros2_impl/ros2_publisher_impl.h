#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "romalcpp/publisher.h"

namespace romalcpp::ros2_impl {

template <class MsgT>
class Ros2PublisherImpl : public romalcpp::Publisher<MsgT> {
 public:
  Ros2PublisherImpl() : romalcpp::Publisher<MsgT>() {}

  void publish(const MsgT& msg) override { ros2_publisher_->publish(msg); }

  void setRos2Publisher(std::shared_ptr<rclcpp::Publisher<MsgT>> ros2_publisher) {
    ros2_publisher_ = std::move(ros2_publisher);
  }

 private:
  std::shared_ptr<rclcpp::Publisher<MsgT>> ros2_publisher_;
};

}  // namespace romalcpp::ros2_impl
