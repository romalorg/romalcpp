#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "romalcpp/subscriber.h"

namespace romalcpp::ros2_impl {

template <class MsgT>
class Ros2SubscriberImpl : public romalcpp::Subscriber<MsgT> {
 public:
  Ros2SubscriberImpl() : romalcpp::Subscriber<MsgT>() {}

  void msgCallback(const MsgT& msg) { callback_(msg); }

  void setCallback(typename romalcpp::Subscriber<MsgT>::CallbackFn callback) {
    callback_ = std::move(callback);
  }

  void setRos2Subscription(std::shared_ptr<rclcpp::Subscription<MsgT>> ros2_subscription) {
    ros2_subscription_ = ros2_subscription;
  }

 private:
  std::shared_ptr<rclcpp::Subscription<MsgT>> ros2_subscription_;
  typename romalcpp::Subscriber<MsgT>::CallbackFn callback_;
};

}  // namespace romalcpp::ros2_impl
