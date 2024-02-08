#include <stdio.h>
#include "core/update.h"
#include "core/shutdown.h"
#include "core/world.h"
#include "platform/video.h"
#include "gfx/primitives.h"
#include "gfx/shaders.h"
#include "gfx/view.h"


int main(int argc, const char** argv)
{
  eath::create_world();
  eath::register_systems();

  const int width = 1500;
  const int height = 900;
  eath::WindowHandle wh = eath::init_window(width, height, 0);
  if (!eath::is_handle_valid(wh))
  {
    printf("Cannot init video\n");
    return 1;
  }

  flecs::world& ecs = eath::get_world();

  flecs::entity vseid = ecs.entity().set(eath::ShaderName{"simple_vs"});
  flecs::entity fseid = ecs.entity().set(eath::ShaderName{"simple_fs"});
  //flecs::entity progeid = ecs.entity().set(ShaderProgram{vseid, fseid});

  flecs::entity box = ecs.entity()
    .set(eath::Box{bx::Vec3{1, 2, 3}})
    .set(eath::ShaderProgram{vseid, fseid});

  flecs::entity cameraView = ecs.entity()
    .set(eath::CameraPosition{{0, 0, -15}})
    .set(eath::CameraYPR{{0, 0, 0}})
    .set(eath::CameraMatrix{})
    .set(eath::ViewMatrix{})
    .set(eath::ProjMatrix{});

  while (eath::mainloop())
  {
  }
  eath::shutdown(wh);

  return 0;
}

