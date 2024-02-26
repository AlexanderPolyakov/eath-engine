#pragma once

#include "core/flecs_helpers.h"

extern ECS_COMPONENT_DECLARE(texture__path);
extern ECS_COMPONENT_DECLARE(texture__handle);

namespace eath
{
  void register_textures(ecs_world_t* ecs);
};

