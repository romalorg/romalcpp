#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "romalcpp/node.h"
#include "romalcpp/publisher.h"
#include "romalcpp/ros2_impl/ros2_publisher_impl.h"
#include "romalcpp/ros2_impl/ros2_subscriber_impl.h"
#include "romalcpp/ros2_impl/ros2_timer_impl.h"
#include "romalcpp/subscriber.h"
#include "romalcpp/timer.h"

namespace romalcpp::ros2_impl {

class Ros2NodeImpl {
 public:
  explicit Ros2NodeImpl(const std::string& name)
      : ros2_node_{std::make_shared<rclcpp::Node>(name)} {}

  void run() {
    rclcpp::spin(ros2_node_);
    rclcpp::shutdown();
  }

  template <class MsgT>
  std::shared_ptr<romalcpp::Publisher<MsgT>> createPublisher(const std::string& topic,
                                                             int queue_size) {
    auto publisher = std::make_shared<Ros2PublisherImpl<MsgT>>();
    publisher->setRos2Publisher(ros2_node_->create_publisher<MsgT>(topic, queue_size));
    return publisher;
  }

  template <class MsgT>
  std::shared_ptr<romalcpp::Subscriber<MsgT>> createSubscriber(
      const std::string& topic, int queue_size,
      typename romalcpp::Subscriber<MsgT>::CallbackFn callback) {
    auto subscriber = std::make_shared<Ros2SubscriberImpl<MsgT>>();
    subscriber->setCallback(std::move(callback));
    // Pass a raw pointer to the callback to avoid a reference loop.
    Ros2SubscriberImpl<MsgT>* subscriber_ptr = subscriber.get();
    std::shared_ptr<rclcpp::Subscription<MsgT>> ros2_subscription =
        ros2_node_->create_subscription<MsgT>(topic, queue_size, [subscriber_ptr](const MsgT& msg) {
          subscriber_ptr->msgCallback(msg);
        });
    subscriber->setRos2Subscription(std::move(ros2_subscription));
    return subscriber;
  }

  template <typename DurationRepT, typename DurationT>
  std::shared_ptr<romalcpp::Timer> createTimer(
      std::chrono::duration<DurationRepT, DurationT> period, romalcpp::Timer::CallbackFn callback) {
    auto timer = std::make_shared<Ros2TimerImpl>();
    timer->setRos2Timer(ros2_node_->create_wall_timer(period, callback));
    return timer;
  }

 private:
  std::shared_ptr<rclcpp::Node> ros2_node_;
};

std::shared_ptr<romalcpp::Node<Ros2NodeImpl>> CreateNode(const std::string& name, int argc,
                                                         char** argv);

}  // namespace romalcpp::ros2_impl
