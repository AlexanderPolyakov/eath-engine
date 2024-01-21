#pragma once

#include <cstdint>

namespace eath
{
  // TODO: redo to a fully ECS driven res handles. We don't need res handles if they're managed by ECS
  using ResHandle = uint32_t;
  constexpr ResHandle invalid_handle = uint32_t(-1);

  inline bool is_handle_valid(ResHandle handle) { return handle != invalid_handle; }
};

