#pragma once

extern ECS_COMPONENT_DECLARE(vertex_buffer_handle);
extern ECS_COMPONENT_DECLARE(index_buffer_handle);

namespace eath
{
  void register_buffers(ecs_world_t* ecs);
};

