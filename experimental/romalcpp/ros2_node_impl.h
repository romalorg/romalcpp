#pragma once

#include "rclcpp/rclcpp.hpp"
#include "romalcpp/msg_converter_traits.h"
#include "romalcpp/node.h"

namespace romalcpp_ros2 {

template <class ObjT, class MsgT>
class Ros2Subscriber : public romalcpp::Subscriber<ObjT> {
 public:
  Ros2Subscriber() = default;

  void msgCallback(MsgT msg) {
    ObjT obj = romalcpp::MsgConverterTraits<ObjT>::convert(msg);
    callback_(obj);
  }

  void setCallback(std::function<void(ObjT)> callback) { callback_ = std::move(callback); }

  void setRos2Subscription(std::shared_ptr<rclcpp::Subscription<MsgT>> ros2_subscription) {
    ros2_subscription_ = ros2_subscription;
  }

 private:
  std::shared_ptr<rclcpp::Subscription<MsgT>> ros2_subscription_;
  std::function<void(ObjT)> callback_;
};

class Ros2Node : public romalcpp::Node<Ros2Node> {
 public:
  explicit Ros2Node(const std::string& name)
      : Node(name), ros2_node_{std::make_shared<rclcpp::Node>(name)} {}

  void init() override {
    const std::vector<const char*> argv{"foo"};
    rclcpp::init(0, argv.data());
  }

  void run() override {
    rclcpp::spin(ros2_node_);
    rclcpp::shutdown();
  }

  template <class ObjT>
  std::shared_ptr<romalcpp::Publisher<ObjT>> createPublisherImpl(const std::string& /*topic*/) {
    throw std::runtime_error{"Not implemented"};
  }

  template <class ObjT>
  std::shared_ptr<romalcpp::Subscriber<ObjT>> createSubscriberImpl(
      const std::string& topic, int queue_size,
      typename romalcpp::Subscriber<ObjT>::CallbackFn callback) {
    using MsgT = typename romalcpp::MsgConverterTraits<ObjT>::FromType;
    auto subscriber = std::make_shared<Ros2Subscriber<ObjT, MsgT>>();
    subscriber->setCallback(std::move(callback));
    // Pass a raw pointer to the callback to avoid a reference loop.
    Ros2Subscriber<ObjT, MsgT>* subscriber_ptr = subscriber.get();
    std::shared_ptr<rclcpp::Subscription<MsgT>> ros2_subscription =
        ros2_node_->create_subscription<MsgT>(
            topic, queue_size, [subscriber_ptr](MsgT msg) { subscriber_ptr->msgCallback(msg); });
    subscriber->setRos2Subscription(std::move(ros2_subscription));
    return subscriber;
  }

 private:
  std::shared_ptr<rclcpp::Node> ros2_node_;
};

std::shared_ptr<romalcpp::Node<Ros2Node>> CreateNode(const std::string& name, int argc,
                                                     char** argv);

}  // namespace romalcpp_ros2
