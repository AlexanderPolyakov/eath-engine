#include "gfx/shaders.h"
#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>
#include <bx/debug.h>
#include <bx/file.h>
#include "core/flecs_helpers.h"


// TODO: Isolate and move somewhere it belongs
#define DBG_STRINGIZE(_x) DBG_STRINGIZE_(_x)
#define DBG_STRINGIZE_(_x) #_x
#define DBG_FILE_LINE_LITERAL "" __FILE__ "(" DBG_STRINGIZE(__LINE__) "): "
#define DBG(_format, ...) bx::debugPrintf(DBG_FILE_LINE_LITERAL "" _format "\n", ##__VA_ARGS__)

static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
{
  if (bx::open(_reader, _filePath) )
  {
    uint32_t size = (uint32_t)bx::getSize(_reader);
    const bgfx::Memory* mem = bgfx::alloc(size+1);
    bx::read(_reader, mem->data, size, bx::ErrorAssert{});
    bx::close(_reader);
    mem->data[mem->size-1] = '\0';
    return mem;
  }

  DBG("Failed to load %s.", _filePath);
  return NULL;
}

static void* loadMem(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size)
{
  if (bx::open(_reader, _filePath) )
  {
    uint32_t size = (uint32_t)bx::getSize(_reader);
    void* data = bx::alloc(_allocator, size);
    bx::read(_reader, data, size, bx::ErrorAssert{});
    bx::close(_reader);

    if (NULL != _size)
    {
      *_size = size;
    }
    return data;
  }

  DBG("Failed to load %s.", _filePath);
  return NULL;
}


static bgfx::ShaderHandle loadShader(bx::FileReaderI* _reader, const char* _name)
{
  char filePath[512];

  const char* shaderPath = "???";

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

  bx::strCopy(filePath, BX_COUNTOF(filePath), shaderPath);
  bx::strCat(filePath, BX_COUNTOF(filePath), _name);
  bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");

  bgfx::ShaderHandle handle = bgfx::createShader(loadMem(_reader, filePath) );
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
  bx::FileReader fr;
  bgfx::ShaderHandle sh = loadShader(&fr, shaders__path.c_str());
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

void eath::register_shaders(flecs::world& ecs)
{
  ecs_component_named(ecs, shaders__path, std::string);
  ecs_component_named(ecs, shaders__vertex_shader, ecs_entity_t);
  ecs_component_named(ecs, shaders__fragment_shader, ecs_entity_t);
  ecs_component_named(ecs, shaders__handle, bgfx::ShaderHandle);
  ecs_component_named(ecs, shaders__program_handle, bgfx::ProgramHandle);

  ECS_OBSERVER(ecs, on_shader_path_set, EcsOnSet, shaders__path);
  ECS_OBSERVER(ecs, on_shader_program_set, EcsOnSet, shaders__vertex_shader, shaders__fragment_shader);
}

