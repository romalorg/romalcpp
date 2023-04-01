#pragma once

#define ROMAL_REGISTER_MSG_CONVERTER(ToT, FromT, ConverterFn)                                      \
  namespace romalcpp {                                                                             \
  template <>                                                                                      \
  struct MsgConverterTraits<ToT> {                                                                 \
    using FromType = FromT;                                                                        \
    using ToType = ToT;                                                                            \
    static ToType convert(FromType& from) { return ConverterFn(from); }                            \
  };                                                                                               \
  }  // namespace romalcpp

namespace romalcpp {

template <typename FromT>
struct MsgConverterTraits;

}  // namespace romalcpp
