#pragma once

#include <flecs.h>
#include <bx/math.h>

extern ECS_COMPONENT_DECLARE(box__half_extents);

namespace eath
{
  void register_primitives(ecs_world_t* ecs);
};

