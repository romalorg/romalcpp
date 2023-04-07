#pragma once

namespace romalcpp {

template <class MsgT>
class Publisher {
 public:
  virtual void publish(const MsgT& msg) = 0;

  virtual ~Publisher() = default;
  Publisher() = default;
  Publisher(const Publisher&) = delete;
  Publisher(Publisher&&) noexcept = default;
  Publisher& operator=(const Publisher&) = delete;
  Publisher& operator=(Publisher&&) noexcept = default;
};

}  // namespace romalcpp
