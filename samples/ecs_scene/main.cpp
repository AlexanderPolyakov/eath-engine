#include <stdio.h>
#include "core/update.h"
#include "core/shutdown.h"
#include "core/world.h"
#include "platform/video.h"
#include "gfx/primitives.h"
#include "gfx/shaders.h"


int main(int argc, const char** argv)
{
  const int width = 1500;
  const int height = 900;
  eath::WindowHandle wh = eath::init_window(width, height, 0);
  if (!eath::is_handle_valid(wh))
  {
    printf("Cannot init video\n");
    return 1;
  }

  eath::create_world();
  eath::register_systems();

  flecs::world& ecs = eath::get_world();

  flecs::entity vseid = ecs.entity().set(eath::ShaderName{"simple_vs.bin"});
  flecs::entity fseid = ecs.entity().set(eath::ShaderName{"simple_fs.bin"});
  //flecs::entity progeid = ecs.entity().set(ShaderProgram{vseid, fseid});

  flecs::entity box = ecs.entity().set(eath::Box{bx::Vec3{2, 3, 5}}).set(eath::ShaderProgram{vseid, fseid});

  while (eath::mainloop())
  {
  }
  eath::shutdown(wh);

  return 0;
}

