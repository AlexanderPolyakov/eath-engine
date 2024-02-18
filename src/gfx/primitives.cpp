#include "gfx/primitives.h"
#include "gfx/vertex_format.h"
#include "gfx/buffer.h"
#include "core/bx_math.h"
#include "core/flecs_helpers.h"

#include <array>

#include <iostream>

ECS_COMPONENT_DECLARE(box__half_extents);

static float bool_to_sign(bool sign) { return sign ? 1.f : -1.f; }

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static bgfx::VertexLayout posVtxLayout;
static bgfx::VertexLayout posColVtxLayout;

void on_box_prim_set(ecs_world_t* ecs, ecs_entity_t e, const bx::Vec3& box__half_extents)
{
  constexpr uint16_t boxIndices[] =
  {
    0, 4, 6, 0, 6, 2,
    1, 5, 4, 1, 4, 0,
    3, 7, 5, 3, 5, 1,
    2, 6, 7, 2, 7, 3,
    5, 7, 6, 5, 6, 4,
    1, 0, 2, 1, 2, 3
  };
  eath::VtxPosCol vertices[8];
  for (size_t i = 0; i < 8; ++i)
  {
    bx::Vec3 signs{bool_to_sign(i & 1), bool_to_sign(i & 2), bool_to_sign(i & 4)};
    bx::Vec3 pos = mul(box__half_extents, signs);
    vertices[i].x = pos.x;
    vertices[i].y = pos.y;
    vertices[i].z = pos.z;
    vertices[i].argb = 0xffffffff;
  }
  //
  //   1---0
  //  /|  /|
  // 5---4 |
  // | 3 | 2
  // |/  |/
  // 7---6
  //
  // ^y /z
  // | /
  // |/
  // +----> x
  //
  bgfx::VertexLayout posColVtxLayout;
  posColVtxLayout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();

  bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::copy(vertices, sizeof(vertices)), posColVtxLayout);
  bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::copy(boxIndices, sizeof(boxIndices)));
  ecs_cset_named(ecs, e, vertex_buffer_handle, vbh);
  ecs_cset_named(ecs, e, index_buffer_handle, ibh);
}

void on_box_prim_set(ecs_iter_t* it)
{
  const bx::Vec3* box__half_extents = ecs_field(it, bx::Vec3, 1);
  for (int i = 0; i < it->count; ++i)
    on_box_prim_set(it->world, it->entities[i], box__half_extents[i]);
}

void eath::register_primitives(flecs::world& ecs)
{
  ecs_component_named(ecs, box__half_extents, bx::Vec3);

  posVtxLayout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .end();

  posColVtxLayout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();

  ECS_OBSERVER(ecs, on_box_prim_set, EcsOnSet, [in] box__half_extents);
}

