#include "romalcpp/ros2_impl/ros2_node_impl.h"

namespace romalcpp::ros2_impl {

std::shared_ptr<romalcpp::Node<Ros2NodeImpl>> CreateNode(const std::string& name, int argc,
                                                         char** argv) {
  rclcpp::init(argc, argv);
  auto node_impl = std::make_shared<Ros2NodeImpl>(name);
  return std::make_shared<romalcpp::Node<Ros2NodeImpl>>(name, std::move(node_impl));
}

}  // namespace romalcpp::ros2_impl
