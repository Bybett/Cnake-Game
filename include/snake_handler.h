#ifndef SNAKE_HANDLER_
#define SNAKE_HANDLER_

#include "global_structs.h"

void growSnake(Player *player, Entity **body, TextureStruct texture_data);

void shrinkSnake(Player *player, Entity **body, TextureStruct texture_data);

void setSnake(Entity **body, TextureStruct texture_data);

#endif
