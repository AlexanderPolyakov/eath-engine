#include <flecs.h>
#include "core/flecs_helpers.h"

ecs_query_t* eath::build_query(ecs_world_t* ecs, const char* expr)
{
  ecs_query_desc_t desc = {0};
  desc.filter.expr = expr;
  return ecs_query_init(ecs, &desc);
}

