#pragma once
#include "math/matrix.h"

extern ECS_COMPONENT_DECLARE(camera_position);
extern ECS_COMPONENT_DECLARE(camera_ypr);
extern ECS_COMPONENT_DECLARE(camera_matrix);
extern ECS_COMPONENT_DECLARE(view_matrix);
extern ECS_COMPONENT_DECLARE(proj_matrix);

namespace eath
{
  void register_view(flecs::world& ecs);
};

