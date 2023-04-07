#pragma once

#include <functional>

namespace romalcpp {

class Timer {
 public:
  using CallbackFn = std::function<void()>;

  virtual ~Timer() = default;
  Timer() = default;
  Timer(const Timer&) = delete;
  Timer(Timer&&) noexcept = default;
  Timer& operator=(const Timer&) = delete;
  Timer& operator=(Timer&&) noexcept = default;
};

}  // namespace romalcpp
