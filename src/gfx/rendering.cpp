#include <bgfx/bgfx.h>
#include "gfx/rendering.h"
#include "gfx/buffer.h"
#include <bx/math.h>
#include "gfx/view.h"
#include "core/flecs_helpers.h"

ECS_COMPONENT_DECLARE(transform);


static void render_geometry(const eath::Mat4x4& transform,
                            const bgfx::VertexBufferHandle& vertex_buffer_handle,
                            const bgfx::IndexBufferHandle& index_buffer_handle,
                            const bgfx::ProgramHandle& shaders__program_handle)
{
  bgfx::setTransform(transform.m);

  bgfx::setVertexBuffer(0, vertex_buffer_handle);
  bgfx::setIndexBuffer(index_buffer_handle);

  bgfx::submit(0, shaders__program_handle);
}

static void render_geometry(ecs_iter_t* it)
{
  const eath::Mat4x4* transform = ecs_field(it, eath::Mat4x4, 1);
  const bgfx::VertexBufferHandle* vertex_buffer_handle = ecs_field(it, bgfx::VertexBufferHandle, 2);
  const bgfx::IndexBufferHandle* index_buffer_handle = ecs_field(it, bgfx::IndexBufferHandle, 3);
  const bgfx::ProgramHandle* shaders__program_handle = ecs_field(it, bgfx::ProgramHandle, 4);
  for (int i = 0; i < it->count; ++i)
    render_geometry(transform[i], vertex_buffer_handle[i], index_buffer_handle[i], shaders__program_handle[i]);
}


void eath::register_rendering(flecs::world& ecs)
{
  ecs_component_named(ecs, transform, eath::Mat4x4);

  ECS_SYSTEM(ecs, render_geometry, EcsOnUpdate, [in] transform, [in] vertex_buffer_handle, [in] index_buffer_handle, [in] shaders__program_handle);
}

