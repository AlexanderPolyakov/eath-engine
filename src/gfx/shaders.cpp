#include "gfx/shaders.h"
#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>
#include <bx/debug.h>


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

void eath::register_shaders(flecs::world& ecs)
{
}

