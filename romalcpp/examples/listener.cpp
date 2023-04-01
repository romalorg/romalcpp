#include <iostream>
#include <memory>

#include "romalcpp/examples/ros2_msg_converters.h"
#include "romalcpp/ros2_node_impl.h"
#include "std_msgs/msg/string.hpp"

namespace {

constexpr int kSubscriberQueueSize = 10;

}  // namespace

namespace romalcpp::examples {

template <class NodeImpl>
class ListenerNode {
 public:
  explicit ListenerNode(std::shared_ptr<romalcpp::Node<NodeImpl>> node)
      : node_{std::move(node)},
        subscriber_{node_->template createSubscriber<std::string&>(
            "topic", kSubscriberQueueSize, [this](std::string& msg) { this->msgCallback(msg); })} {}

  // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  void msgCallback(std::string& msg) { std::cout << "Received: " << msg << std::endl; };

 private:
  std::shared_ptr<romalcpp::Node<NodeImpl>> node_;
  std::shared_ptr<romalcpp::Subscriber<std::string&>> subscriber_;
};

}  // namespace romalcpp::examples

int main(int argc, char** argv) {
  auto node = romalcpp_ros2::CreateNode("listener", argc, argv);
  romalcpp::examples::ListenerNode listener_node{node};
  node->run();
  return 0;
}
