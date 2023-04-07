#pragma once

#include <any>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace romalcpp {

template <class ObjT>
class Publisher {
 public:
  void publish(const ObjT& obj);
};

template <class ObjT>
class Subscriber {
 public:
  using CallbackFn = std::function<void(ObjT&)>;
};

template <class NodeImpl>
class Node {
 public:
  explicit Node(std::string name, std::shared_ptr<NodeImpl> node_impl)
      : name_{std::move(name)}, node_impl_{std::move(node_impl)} {}

  Node(const Node&) = delete;
  Node(Node&&) = delete;
  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) = delete;
  virtual ~Node() = default;

  std::string name() { return name_; }

  virtual void init() {}
  virtual void run() { throw std::runtime_error{"Unimplemented"}; }

  template <class ObjT>
  std::shared_ptr<Publisher<ObjT>> createPublisher(const std::string& topic) {
    return static_cast<NodeImpl&>(*this).template createPublisherImpl<ObjT>(topic);
  }

  template <class ObjT>
  std::shared_ptr<Subscriber<ObjT>> createSubscriber(
      const std::string& topic, int queue_size, typename Subscriber<ObjT>::CallbackFn callback) {
    return static_cast<NodeImpl&>(*this).template createSubscriberImpl<ObjT>(topic, queue_size,
                                                                             callback);
  }

 private:
  std::string name_;
  std::shared_ptr<NodeImpl> node_impl_;
};

}  // namespace romalcpp
