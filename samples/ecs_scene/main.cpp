#include <stdio.h>
#include "core/update.h"
#include "core/shutdown.h"
#include "core/world.h"
#include "core/input.h"
#include "platform/video.h"
#include "gfx/primitives.h"
#include "gfx/shaders.h"
#include "gfx/view.h"
#include "core/flecs_helpers.h"

#include <SDL3/SDL.h>

// TODO: codegen it, there's no place for something like this here!
struct QueryMouseMotion
{
  static ecs_query_t* q;

  QueryMouseMotion(ecs_world_t* ecs)
  {
    q = eath::build_query(ecs, "[in] mouse_motion");
  }
  template<typename Callable>
  static void execute(ecs_world_t* ecs, Callable c)
  {
    ecs_iter_t it = ecs_query_iter(ecs, q);
    while (ecs_query_next(&it))
    {
      const SDL_MouseMotionEvent* mouse_motion = ecs_field(&it, SDL_MouseMotionEvent, 1);
      for (int i = 0; i < it.count; ++i)
        c(mouse_motion[i]);
    }
  }
};

ecs_query_t* QueryMouseMotion::q = nullptr;

static void control_camera(float dt, ecs_world_t* ecs, bx::Vec3& camera_position, bx::Vec3& camera_ypr)
{
  QueryMouseMotion::execute(ecs, [&](const SDL_MouseMotionEvent& mouse_motion)
    {
      camera_ypr.x -= mouse_motion.xrel * 0.01;
      camera_ypr.y -= mouse_motion.yrel * 0.01;
    });
  const eath::KeyboardState* ks = ecs_get_named_singleton(ecs, keyboard_state, eath::KeyboardState);

  // Query should fix this actually, but queries are more cumbersome at this time to use
  if (ks)
  {
    // dt!
    camera_ypr.x += (ks->curState[SDL_SCANCODE_A] - ks->curState[SDL_SCANCODE_D]) * dt;
    camera_ypr.y += (ks->curState[SDL_SCANCODE_W] - ks->curState[SDL_SCANCODE_S]) * dt;
  }

  const bx::Vec3 dir = {cosf(camera_ypr.x + bx::kPiHalf) * cosf(camera_ypr.y),
                        sinf(camera_ypr.y),
                        sinf(camera_ypr.x + bx::kPiHalf) * cosf(camera_ypr.y)};
  camera_position = mul(dir, -15.f);
}

static void control_camera(ecs_iter_t* it)
{
  bx::Vec3* camera_position = ecs_field(it, bx::Vec3, 1);
  bx::Vec3* camera_ypr = ecs_field(it, bx::Vec3, 2);
  for (int i = 0; i < it->count; ++i)
    control_camera(it->delta_time, it->real_world, camera_position[i], camera_ypr[i]);
}

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

  ecs_entity_t vseid = ecs_new(ecs, 0);
  ecs_set_named(ecs, vseid, shaders__path, std::string, "simple_vs");
  ecs_entity_t fseid = ecs_new(ecs, 0);
  ecs_set_named(ecs, fseid, shaders__path, std::string, "simple_fs");

  ecs_entity_t box = ecs_new(ecs, 0);
  ecs_cset_named(ecs, box, shaders__vertex_shader, vseid);
  ecs_cset_named(ecs, box, shaders__fragment_shader, fseid);
  ecs_set_named(ecs, box, box__half_extents, bx::Vec3, {1, 2, 3});

  ecs_entity_t cameraView = ecs_new(ecs, 0);
  ecs_set_named(ecs, cameraView, camera_position, bx::Vec3, {0, 0, -15});
  ecs_set_named(ecs, cameraView, camera_ypr, bx::Vec3, {0, 0, 0});
  ecs_set_named(ecs, cameraView, camera_matrix, eath::Mat4x4, {});
  ecs_set_named(ecs, cameraView, view_matrix, eath::Mat4x4, {});
  ecs_set_named(ecs, cameraView, proj_matrix, eath::Mat4x4, {});

  QueryMouseMotion q(ecs.c_ptr());
  ECS_SYSTEM(ecs, control_camera, EcsOnUpdate, [in] camera_position, [in] camera_ypr);

  while (eath::mainloop())
  {
  }
  eath::shutdown(wh);

  return 0;
}

