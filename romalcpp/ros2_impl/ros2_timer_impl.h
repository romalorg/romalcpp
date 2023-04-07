#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "romalcpp/timer.h"

namespace romalcpp::ros2_impl {

class Ros2TimerImpl : public romalcpp::Timer {
 public:
  Ros2TimerImpl() = default;

  void setRos2Timer(std::shared_ptr<rclcpp::WallTimer<std::function<void()>>> ros2_timer) {
    ros2_timer_ = std::move(ros2_timer);
  }

 private:
  std::shared_ptr<rclcpp::WallTimer<std::function<void()>>> ros2_timer_;
};

}  // namespace romalcpp::ros2_impl
