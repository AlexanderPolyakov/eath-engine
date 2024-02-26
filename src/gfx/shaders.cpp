#include "gfx/shaders.h"
#include <bgfx/bgfx.h>
#include <bx/debug.h>
#include "core/flecs_helpers.h"
#include "core/bx_file.h"


static bgfx::ShaderHandle loadShader(const char* _name)
{
  std::string shaderPath = "???";

  switch (bgfx::getRendererType() )
  {
    case bgfx::RendererType::Noop:
    case bgfx::RendererType::Direct3D11:
    case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
    case bgfx::RendererType::Agc:
    case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
    case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
    case bgfx::RendererType::Nvn:        shaderPath = "shaders/nvn/";   break;
    case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
    case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
    case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;

    case bgfx::RendererType::Count:
                                         BX_ASSERT(false, "You should not be here!");
                                         break;
  }

  shaderPath += _name;
  shaderPath += ".bin";

  bgfx::ShaderHandle handle = bgfx::createShader(eath::load_mem(shaderPath.c_str()));
  bgfx::setName(handle, _name);

  return handle;
}

ECS_COMPONENT_DECLARE(shaders__path);
ECS_COMPONENT_DECLARE(shaders__vertex_shader);
ECS_COMPONENT_DECLARE(shaders__fragment_shader);
ECS_COMPONENT_DECLARE(shaders__handle);
ECS_COMPONENT_DECLARE(shaders__program_handle);

static void on_shader_path_set(ecs_world_t* ecs, ecs_entity_t e, const std::string& shaders__path)
{
  bgfx::ShaderHandle sh = loadShader(shaders__path.c_str());
  ecs_cset_named(ecs, e, shaders__handle, sh);
}

static void on_shader_program_set(ecs_world_t* ecs, ecs_entity_t e,
                                  ecs_entity_t shaders__vertex_shader, ecs_entity_t shaders__fragment_shader)
{
  const bgfx::ShaderHandle* vertexSh = ecs_get_named(ecs, shaders__vertex_shader, shaders__handle, bgfx::ShaderHandle);
  const bgfx::ShaderHandle* fragmentSh = ecs_get_named(ecs, shaders__fragment_shader, shaders__handle, bgfx::ShaderHandle);
  if (!vertexSh || !fragmentSh)
  {
    if (!vertexSh)
      printf("Cannot find vertex shader handle\n");
    if (!fragmentSh)
      printf("Cannot find fragment shader handle\n");
    return; // TODO: error reporting, this shouldn't happen in well-formed program
  }

  bgfx::ProgramHandle ph = bgfx::createProgram(*vertexSh, *fragmentSh, true);
  ecs_cset_named(ecs, e, shaders__program_handle, ph);
}


static void on_shader_path_set(ecs_iter_t* it)
{
  const std::string* shaders__path = ecs_field(it, std::string, 1);
  for (int i = 0; i < it->count; ++i)
    on_shader_path_set(it->world, it->entities[i], shaders__path[i]);
}

static void on_shader_program_set(ecs_iter_t* it)
{
  const ecs_entity_t* shaders__vertex_shader = ecs_field(it, ecs_entity_t, 1);
  const ecs_entity_t* shaders__fragment_shader = ecs_field(it, ecs_entity_t, 2);
  for (int i = 0; i < it->count; ++i)
    on_shader_program_set(it->world, it->entities[i], shaders__vertex_shader[i], shaders__fragment_shader[i]);
}

void eath::register_shaders(ecs_world_t* ecs)
{
  ecs_component_named(ecs, shaders__path, std::string);
  ecs_component_named(ecs, shaders__vertex_shader, ecs_entity_t);
  ecs_component_named(ecs, shaders__fragment_shader, ecs_entity_t);
  ecs_component_named(ecs, shaders__handle, bgfx::ShaderHandle);
  ecs_component_named(ecs, shaders__program_handle, bgfx::ProgramHandle);

  ECS_OBSERVER(ecs, on_shader_path_set, EcsOnSet, shaders__path);
  ECS_OBSERVER(ecs, on_shader_program_set, EcsOnSet, shaders__vertex_shader, shaders__fragment_shader);
}

