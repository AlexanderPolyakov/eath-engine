#include <flecs.h>
#include <bgfx/bgfx.h>
#include "core/flecs_helpers.h"
#include "gfx/buffer.h"

ECS_COMPONENT_DECLARE(vertex_buffer_handle);
ECS_COMPONENT_DECLARE(index_buffer_handle);


void eath::register_buffers(flecs::world& ecs)
{
  ecs_component_named(ecs, vertex_buffer_handle, bgfx::VertexBufferHandle);
  ecs_component_named(ecs, index_buffer_handle, bgfx::IndexBufferHandle);
}

