#include "romalcpp/examples/listener_node.h"
#include "romalcpp/ros2_impl/ros2_node_impl.h"

int main(int argc, char** argv) {
  auto node = romalcpp::ros2_impl::CreateNode("listener", argc, argv);
  romalcpp::examples::ListenerNode listener_node{node};
  node->run();
  return 0;
}
