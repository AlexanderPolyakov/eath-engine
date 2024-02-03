#pragma once

#include <flecs.h>
#include <bx/math.h>

namespace eath
{
  struct Box
  {
    bx::Vec3 halfExtents = {0.f, 0.f, 0.f};
  };

  void register_primitives(flecs::world& ecs);
};

