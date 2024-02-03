#include "gfx/rendering.h"
#include "gfx/buffer.h"


void eath::register_rendering(flecs::world& ecs)
{
  ecs.system<BufferHandles, bgfx::ProgramHandle>()
    .each([](BufferHandles buffer, bgfx::ProgramHandle program)
    {
      bgfx::setVertexBuffer(0, buffer.vbh);
      bgfx::setIndexBuffer(buffer.ibh);

      bgfx::submit(0, program);
    });
}

