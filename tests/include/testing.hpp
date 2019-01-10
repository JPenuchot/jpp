#pragma once

#include <stdexcept>

inline const auto assert = [](auto&& cond, auto&& message)
{
  if(!cond) throw std::runtime_error(message);
};
