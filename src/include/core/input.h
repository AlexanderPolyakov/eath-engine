#pragma once

extern ECS_COMPONENT_DECLARE(mouse_motion);

namespace eath
{
  void register_input(flecs::world& ecs);
};
