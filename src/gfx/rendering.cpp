#include "gfx/rendering.h"
#include "gfx/buffer.h"
#include <bx/math.h>
#include "gfx/view.h"
#include "core/flecs_helpers.h"

static void cam_matrix_from_pos_ypr(eath::Mat4x4& camera_matrix, const bx::Vec3& camera_position,
                                    const bx::Vec3& camera_ypr)
{
  float cam_rotation[16];
  bx::mtxRotateXYZ(cam_rotation, camera_ypr.y, camera_ypr.x, camera_ypr.z);

  float cam_translation[16];
  bx::mtxTranslate(cam_translation, camera_position.x, camera_position.y, camera_position.z);

  bx::mtxMul(camera_matrix.m, cam_rotation, cam_translation);
}

static void view_matrix_from_cam_matrix(eath::Mat4x4& vm, const eath::Mat4x4& cm)
{
  bx::mtxInverse(vm.m, cm.m);
}

static void set_proj_matrix(eath::Mat4x4& proj)
{
  bx::mtxProj(
      proj.m, 60.0f, float(3000) / float(1800), 0.1f,
      100.0f, bgfx::getCaps()->homogeneousDepth);
}

static void set_view_transform(const eath::Mat4x4& view, const eath::Mat4x4& proj)
{
  bgfx::setViewTransform(0, view.m, proj.m);
}

static void render_geometry(const bgfx::VertexBufferHandle& vertex_buffer_handle, const bgfx::IndexBufferHandle& index_buffer_handle,
                            const bgfx::ProgramHandle& shaders__program_handle)
{
  bgfx::setVertexBuffer(0, vertex_buffer_handle);
  bgfx::setIndexBuffer(index_buffer_handle);

  bgfx::submit(0, shaders__program_handle);
}


// TODO: this should be in a codegen or macro!
static void cam_matrix_from_pos_ypr(ecs_iter_t* it)
{
  eath::Mat4x4* cm = ecs_field(it, eath::Mat4x4, 1);
  const bx::Vec3* pos = ecs_field(it, bx::Vec3, 2);
  const bx::Vec3* ypr = ecs_field(it, bx::Vec3, 3);
  for (int i = 0; i < it->count; ++i)
    cam_matrix_from_pos_ypr(cm[i], pos[i], ypr[i]);
}

static void view_matrix_from_cam_matrix(ecs_iter_t* it)
{
  eath::Mat4x4* vm = ecs_field(it, eath::Mat4x4, 1);
  const eath::Mat4x4* cm = ecs_field(it, eath::Mat4x4, 2);
  for (int i = 0; i < it->count; ++i)
    view_matrix_from_cam_matrix(vm[i], cm[i]);
}

static void set_proj_matrix(ecs_iter_t* it)
{
  eath::Mat4x4* pm = ecs_field(it, eath::Mat4x4, 1);
  for (int i = 0; i < it->count; ++i)
    set_proj_matrix(pm[i]);
}

static void set_view_transform(ecs_iter_t* it)
{
  const eath::Mat4x4* vm = ecs_field(it, eath::Mat4x4, 1);
  const eath::Mat4x4* proj = ecs_field(it, eath::Mat4x4, 2);
  for (int i = 0; i < it->count; ++i)
    set_view_transform(vm[i], proj[i]);
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
  ecs_component_named(ecs, view_matrix, eath::Mat4x4);
  ecs_component_named(ecs, proj_matrix, eath::Mat4x4);
  ecs_component_named(ecs, camera_matrix, eath::Mat4x4);
  ecs_component_named(ecs, camera_position, bx::Vec3);
  ecs_component_named(ecs, camera_ypr, bx::Vec3);

  ECS_SYSTEM(ecs, cam_matrix_from_pos_ypr, EcsOnUpdate, camera_matrix, [in] camera_position, [in] camera_ypr);
  ECS_SYSTEM(ecs, view_matrix_from_cam_matrix, EcsOnUpdate, view_matrix, [in] camera_matrix);
  ECS_SYSTEM(ecs, set_proj_matrix, EcsOnUpdate, proj_matrix);
  ECS_SYSTEM(ecs, set_view_transform, EcsOnUpdate, [in] view_matrix, [in] proj_matrix);

  ECS_SYSTEM(ecs, render_geometry, EcsOnUpdate, [in] vertex_buffer_handle, [in] index_buffer_handle, [in] shaders__program_handle);
}

