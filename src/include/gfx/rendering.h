#pragma once
#include <flecs.h>

extern ECS_COMPONENT_DECLARE(transform);

namespace eath
{
  void register_rendering(flecs::world& ecs);
};

