#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>
#include <bx/debug.h>
#include <bx/file.h>

#include "core/bx_file.h"

#define DBG_STRINGIZE(_x) DBG_STRINGIZE_(_x)
#define DBG_STRINGIZE_(_x) #_x
#define DBG_FILE_LINE_LITERAL "" __FILE__ "(" DBG_STRINGIZE(__LINE__) "): "
#define DBG(_format, ...) bx::debugPrintf(DBG_FILE_LINE_LITERAL "" _format "\n", ##__VA_ARGS__)

static const bgfx::Memory* load_mem(bx::FileReaderI* reader, const char* file_path)
{
  if (bx::open(reader, file_path) )
  {
    uint32_t size = (uint32_t)bx::getSize(reader);
    const bgfx::Memory* mem = bgfx::alloc(size+1);
    bx::read(reader, mem->data, size, bx::ErrorAssert{});
    bx::close(reader);
    mem->data[mem->size-1] = '\0';
    return mem;
  }

  DBG("Failed to load %s.", file_path);
  return nullptr;
}

const bgfx::Memory* eath::load_mem(const char* file_path)
{
  bx::FileReader fr;
  return ::load_mem(&fr, file_path);
}

