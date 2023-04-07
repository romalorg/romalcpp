#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include "romalcpp/publisher.h"
#include "romalcpp/subscriber.h"
#include "romalcpp/timer.h"

namespace romalcpp {

template <class NodeImpl>
class Node {
 public:
  explicit Node(std::string name, std::shared_ptr<NodeImpl> node_impl)
      : name_{std::move(name)}, node_impl_{std::move(node_impl)} {}

  Node(const Node&) = delete;
  Node(Node&&) noexcept = default;
  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) noexcept = default;
  virtual ~Node() = default;

  std::string name() { return name_; }
  void run() { node_impl_->run(); }

  template <class MsgT>
  std::shared_ptr<Publisher<MsgT>> createPublisher(const std::string& topic, int queue_size) {
    return node_impl_->template createPublisher<MsgT>(topic, queue_size);
  }

  template <class MsgT>
  std::shared_ptr<Subscriber<MsgT>> createSubscriber(
      const std::string& topic, int queue_size, typename Subscriber<MsgT>::CallbackFn callback) {
    return node_impl_->template createSubscriber<MsgT>(topic, queue_size, callback);
  }

  template <typename DurationRepT, typename DurationT>
  std::shared_ptr<Timer> createTimer(std::chrono::duration<DurationRepT, DurationT> period,
                                     Timer::CallbackFn callback) {
    return node_impl_->template createTimer(period, callback);
  }

 private:
  std::string name_;
  std::shared_ptr<NodeImpl> node_impl_;
};

}  // namespace romalcpp
