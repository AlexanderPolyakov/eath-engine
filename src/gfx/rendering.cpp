#include "gfx/rendering.h"
#include "gfx/buffer.h"
#include <bx/math.h>
#include "gfx/view.h"

void eath::register_rendering(flecs::world& ecs)
{
  ecs.system<CameraMatrix, const CameraPosition, const CameraYPR>()
    .each([](CameraMatrix& cam_mat, const CameraPosition& cp, const CameraYPR& ypr)
        {
          float cam_rotation[16];
          bx::mtxRotateXYZ(cam_rotation, ypr.ypr.y, ypr.ypr.x, ypr.ypr.z);

          float cam_translation[16];
          bx::mtxTranslate(cam_translation, cp.pos.x, cp.pos.y, cp.pos.z);

          bx::mtxMul(cam_mat.m, cam_rotation, cam_translation);
        });
  ecs.system<ViewMatrix, const CameraMatrix>()
    .each([](ViewMatrix& view, const CameraMatrix& cam_mat)
        {
          bx::mtxInverse(view.m, cam_mat.m);
        });

  ecs.system<ProjMatrix>()
    .each([](ProjMatrix& proj)
        {
          bx::mtxProj(
              proj.m, 60.0f, float(3000) / float(1800), 0.1f,
              100.0f, bgfx::getCaps()->homogeneousDepth);
        });

  ecs.system<const ViewMatrix, const ProjMatrix>()
    .each([](const ViewMatrix& view, const ProjMatrix& proj)
        {
          bgfx::setViewTransform(0, view.m, proj.m);
        });

  ecs.system<BufferHandles, bgfx::ProgramHandle>()
    .each([](BufferHandles buffer, bgfx::ProgramHandle program)
    {
      bgfx::setVertexBuffer(0, buffer.vbh);
      bgfx::setIndexBuffer(buffer.ibh);

      bgfx::submit(0, program);
    });
}

