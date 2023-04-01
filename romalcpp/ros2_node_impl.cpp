#include "romalcpp/ros2_node_impl.h"

namespace romalcpp_ros2 {

std::shared_ptr<romalcpp::Node<romalcpp_ros2::Ros2Node>> CreateNode(const std::string& name,
                                                                    int argc, char** argv) {
  rclcpp::init(argc, argv);
  return static_cast<std::shared_ptr<romalcpp::Node<romalcpp_ros2::Ros2Node>>>(
      std::make_shared<romalcpp_ros2::Ros2Node>(name));
}

}  // namespace romalcpp_ros2
