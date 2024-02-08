#include "gfx/primitives.h"
#include "gfx/vertex_format.h"
#include "gfx/buffer.h"
#include "core/bx_math.h"

#include <array>

#include <iostream>

static float bool_to_sign(bool sign) { return sign ? 1.f : -1.f; }

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

void eath::register_primitives(flecs::world& ecs)
{
  static bgfx::VertexLayout posVtxLayout;
  posVtxLayout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .end();

  static bgfx::VertexLayout posColVtxLayout;
  posColVtxLayout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();

  ecs.observer<const Box>()
    .event(flecs::OnSet)
    .each([&](flecs::entity eid, const Box& box)
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
          VtxPosCol vertices[8];
          for (size_t i = 0; i < 8; ++i)
          {
            bx::Vec3 signs{bool_to_sign(i & 1), bool_to_sign(i & 2), bool_to_sign(i & 4)};
            bx::Vec3 pos = mul(box.halfExtents, signs);
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
          eid.set(BufferHandles{vbh, ibh});
        });
}
