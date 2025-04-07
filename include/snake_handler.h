#ifndef SNAKE_HANDLER_
#define SNAKE_HANDLER_

#include "global_structs.h"
#include "global_defines.h"

void rotate_head(Player player, int direction);

void rotate_body(Entity *body);

void cut_snake(Entity *body);

#endif
