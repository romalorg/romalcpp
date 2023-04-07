#pragma once

#include <functional>

namespace romalcpp {

template <class MsgT>
class Subscriber {
 public:
  using CallbackFn = std::function<void(const MsgT&)>;

  virtual ~Subscriber() = default;
  Subscriber() = default;
  Subscriber(const Subscriber&) = delete;
  Subscriber(Subscriber&&) noexcept = default;
  Subscriber& operator=(const Subscriber&) = delete;
  Subscriber& operator=(Subscriber&&) noexcept = default;
};

}  // namespace romalcpp
