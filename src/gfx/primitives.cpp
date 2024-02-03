#include "gfx/primitives.h"
#include "gfx/vertex_format.h"
#include "gfx/buffer.h"
#include "core/bx_math.h"

#include <array>

#include <iostream>

static float bool_to_sign(bool sign) { return sign ? 1.f : -1.f; }

void eath::register_primitives(flecs::world& ecs)
{
  bgfx::VertexLayout posVtxLayout;
  posVtxLayout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .end();

  int boxIndices[] =
  {
    0, 4, 6, 0, 6, 2,
    1, 5, 4, 1, 4, 0,
    3, 7, 5, 3, 5, 1,
    2, 6, 7, 2, 7, 3,
    5, 7, 6, 5, 6, 4,
    1, 0, 2, 1, 2, 3
  };

  ecs.observer<const Box>()
    .event(flecs::OnSet)
    .each([&](flecs::entity eid, const Box& box)
        {
          VtxPos vertices[8];
          for (size_t i = 0; i < 8; ++i)
          {
            bx::Vec3 signs{bool_to_sign(i & 1), bool_to_sign(i & 2), bool_to_sign(i & 4)};
            vertices[i].pos = mul(box.halfExtents, signs);
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

          bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::copy(vertices, sizeof(vertices)), posVtxLayout);
          bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(boxIndices, sizeof(boxIndices)));
          eid.set(BufferHandles{vbh, ibh});
        });
}

