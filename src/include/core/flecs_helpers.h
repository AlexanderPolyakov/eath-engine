#pragma once

#define ecs_set_named(world, entity, name, type, ...)\
  {\
    type&& temp = __VA_ARGS__;\
    ecs_set_id((flecs::world_t*)world, entity.id(), ecs_id(name), sizeof(type), &temp);\
  }

#define ecs_set_named_singleton(world, name, type, ...)\
  {\
    type&& temp = __VA_ARGS__;\
    ecs_set_id((flecs::world_t*)world, ecs_id(name), ecs_id(name), sizeof(type), &temp);\
  }

#define ecs_cset_named_singleton(world, name, comp)\
  ecs_set_id((flecs::world_t*)world, ecs_id(name), ecs_id(name), sizeof(comp), &comp);\

//flecs::set<type>((flecs::world_t*)&world, entity.id(), __VA_ARGS__, ecs_id(name))

#define ecs_component_define_named(world, id_, typ) \
    {\
        ecs_component_desc_t desc = {0}; \
        ecs_entity_desc_t edesc = {0}; \
        edesc.id = ecs_id(id_); \
        edesc.use_low_id = true; \
        edesc.name = #id_; \
        edesc.symbol = #id_; \
        desc.entity = ecs_entity_init(world, &edesc); \
        desc.type.size = ECS_SIZEOF(typ); \
        desc.type.alignment = ECS_ALIGNOF(typ); \
        ecs_id(id_) = ecs_component_init(world, &desc);\
    }\
    ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL)


#define ecs_component_named(world, id, type)\
    ecs_id(id) = 0;\
    ecs_component_define_named(world, id, type);\
    (void)ecs_id(id)

namespace eath
{
  ecs_query_t* build_query(ecs_world_t* ecs, const char* expr);
};

