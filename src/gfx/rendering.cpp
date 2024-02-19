#include <bgfx/bgfx.h>
#include "gfx/rendering.h"
#include "gfx/buffer.h"
#include <bx/math.h>
#include "gfx/view.h"
#include "core/flecs_helpers.h"

static void render_geometry(const bgfx::VertexBufferHandle& vertex_buffer_handle, const bgfx::IndexBufferHandle& index_buffer_handle,
                            const bgfx::ProgramHandle& shaders__program_handle)
{
  bgfx::setVertexBuffer(0, vertex_buffer_handle);
  bgfx::setIndexBuffer(index_buffer_handle);

  bgfx::submit(0, shaders__program_handle);
}

static void render_geometry(ecs_iter_t* it)
{
  const bgfx::VertexBufferHandle* vertex_buffer_handle = ecs_field(it, bgfx::VertexBufferHandle, 1);
  const bgfx::IndexBufferHandle* index_buffer_handle = ecs_field(it, bgfx::IndexBufferHandle, 2);
  const bgfx::ProgramHandle* shaders__program_handle = ecs_field(it, bgfx::ProgramHandle, 3);
  for (int i = 0; i < it->count; ++i)
    render_geometry(vertex_buffer_handle[i], index_buffer_handle[i], shaders__program_handle[i]);
}


void eath::register_rendering(flecs::world& ecs)
{
  ECS_SYSTEM(ecs, render_geometry, EcsOnUpdate, [in] vertex_buffer_handle, [in] index_buffer_handle, [in] shaders__program_handle);
}

