#pragma once

#include <bx/math.h>

namespace eath
{
  struct VtxPos
  {
    bx::Vec3 pos = bx::InitNoneTag{};
  };

  struct VtxPosUV
  {
    bx::Vec3 pos;
    float u, v;
  };
};
