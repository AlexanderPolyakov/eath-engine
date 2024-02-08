#pragma once

#include <bx/math.h>

namespace eath
{
  struct VtxPos
  {
    bx::Vec3 pos = bx::InitNoneTag{};
  };

  struct VtxPosCol
  {
    float x, y, z;
    uint32_t argb;
  };

  struct VtxPosUV
  {
    bx::Vec3 pos;
    float u, v;
  };
};
