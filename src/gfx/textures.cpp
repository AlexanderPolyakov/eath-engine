#include <flecs.h>
#include <string>
#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>
#include "gfx/textures.h"
#include "core/bx_file.h"

ECS_COMPONENT_DECLARE(texture__path);
ECS_COMPONENT_DECLARE(texture__handle);

static bx::DefaultAllocator s_allocator;

static void imageReleaseCb(void* _ptr, void* ctx)
{
  BX_UNUSED(_ptr);
  bimg::ImageContainer* cont = (bimg::ImageContainer*)ctx;
  bimg::imageFree(cont);
}

void unload(void* _ptr)
{
  bx::free(&s_allocator, _ptr);
}

static void on_texture_path_set(ecs_world_t* ecs, ecs_entity_t e, const std::string& texture__path)
{
  const bgfx::Memory* mem = eath::load_mem(texture__path.c_str());
  bimg::ImageContainer* cont = bimg::imageParse(&s_allocator, mem->data, mem->size);
  const bgfx::Memory* memRef = bgfx::makeRef(cont->m_data, cont->m_size, imageReleaseCb, cont);
  unload(mem->data);

  bgfx::TextureHandle handle = bgfx::createTexture2D(
      (uint16_t)cont->m_width,
      (uint16_t)cont->m_height,
      cont->m_numLayers > 1,
      cont->m_numLayers,
      bgfx::TextureFormat::Enum(cont->m_format),
      BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE, // TODO: change to flags passed by the user
      memRef);
  ecs_cset_named(ecs, e, texture__handle, handle);
}

static void on_texture_path_set(ecs_iter_t* it)
{
  const std::string* texture__path = ecs_field(it, std::string, 1);
  for (int i = 0; i < it->count; ++i)
    on_texture_path_set(it->world, it->entities[i], texture__path[i]);
}

void eath::register_textures(ecs_world_t* ecs)
{
  ecs_component_named(ecs, texture__path, std::string);
  ecs_component_named(ecs, texture__handle, bgfx::TextureHandle);

  ECS_OBSERVER(ecs, on_texture_path_set, EcsOnSet, [in] texture__path);
}

