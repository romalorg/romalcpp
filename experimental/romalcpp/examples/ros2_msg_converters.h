#pragma once

#include <string>

#include "romalcpp/msg_converter_traits.h"
#include "std_msgs/msg/string.hpp"

namespace romalcpp::examples {

std::string& StdStringFromRosStdMsgsString(std_msgs::msg::String& ros_msg);
std_msgs::msg::String RosStdMsgsStringFromStdString(std::string& str);

}  // namespace romalcpp::examples

ROMAL_REGISTER_MSG_CONVERTER(std::string&, std_msgs::msg::String,
                             romalcpp::examples::StdStringFromRosStdMsgsString);
ROMAL_REGISTER_MSG_CONVERTER(std_msgs::msg::String, std::string,
                             romalcpp::examples::RosStdMsgsStringFromStdString);
