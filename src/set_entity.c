#include "set_entity.h"
#include "arr_length.h"
#include "global_defines.h"
#include "global_structs.h"
#include "entity_defines.h"
#include "char_to_int_entity.h"
#include "asset_loader.h"
#include <stdlib.h>
#include <time.h>

#define MAX_RANDOM 100

void setEntity(char entity_type, int row, int col,
               Entity entity_list[ENTITY_TYPES][ENTITY_COUNT], TextureStruct texture_data)
{
  int int_type = char_to_int_entity(entity_type);
  int length = entityArrLength(entity_list[int_type]);
  srand(time(NULL));
  int rand_num = rand() % MAX_RANDOM;
  int dir = LEFT;
  Texture2D entity_texture = *texture_data.array[TEXTURE_MISSING];

  if (entity_type >= 'A' && entity_type <= 'Z') {
    if (rand_num > 50) {
      dir = UP;
    } else {
      dir = DOWN;
    }
  } else if (entity_type >= 'a' && entity_type <= 'z') {
    if (rand_num > 50) {
      dir = LEFT;
    } else {
      dir = RIGHT;
    }
  }
  switch (int_type) {
    case BOUNCER:
      entity_list[int_type][length] = (Entity) {
        entity_type,
        YELLOW,
        dir,
        {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE},
        entity_texture
      };
      break;
    case PATROLLER:
      entity_list[int_type][length] = (Entity) {
        entity_type,
        YELLOW,
        dir,
        {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE},
        entity_texture
      };
      break;
  }
}

