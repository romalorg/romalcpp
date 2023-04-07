#include "romalcpp/examples/talker_node.h"
#include "romalcpp/ros2_impl/ros2_node_impl.h"

int main(int argc, char** argv) {
  auto node = romalcpp::ros2_impl::CreateNode("talker", argc, argv);
  romalcpp::examples::TalkerNode talker_node{node};
  node->run();
  return 0;
}
