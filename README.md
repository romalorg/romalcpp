# RoMAL CPP

RoMAL is the Robot Middleware Abstraction Layer. It defines a generic interface for middleware to make it easy to switch between different middleware implementations.

ROS2 is supported natively so far, but the goal is to make it easy to wrap other middleware implementations and switch between them without changing your code (much).

By using this library instead of directly using a particular middleware, it also makes it possible to inject additional features that might be important to you which are not natively supported by a particulra middleware. For example, you could create custom metrics for all publishers. As another example, you can implement logic for all subscribers to detect and report dropped messages.

## Requirements

Bazel 6.1 or greater is required. It is recommended to use bazelisk instead of directly installing a particular version of bazel.

## Running the examples

There are two examples defined in the `//romalcpp/examples` package: listener and talker.

Run the ROS2 listener example:

```bash
bazel run //romalcpp/examples/ros2:listener
```

In another terminal:

Run the ROS2 talker example:

```bash
bazel run //romalcpp/examples/ros2:talker
```
