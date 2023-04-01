#include "romalcpp/examples/ros2_msg_converters.h"

namespace romalcpp::examples {

std::string& StdStringFromRosStdMsgsString(std_msgs::msg::String& ros_msg) { return ros_msg.data; }

std_msgs::msg::String RosStdMsgsStringFromStdString(std::string& str) {
  std_msgs::msg::String ros_msg;
  ros_msg.data = str;
  return ros_msg;
}

}  // namespace romalcpp::examples
