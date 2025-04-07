#include "level_loader.h"
#include "set_entity.h"
#include "entity_defines.h"
#include "arr_length.h"
#include "entity_defines.h"
#include "global_defines.h"
#include "global_structs.h"
#include "asset_loader.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

char load_file(const char *file_name, char raw_level[ROWS][COLS]) {
  FILE *file;
  int row = 0;
  char buffer[35];
  file = fopen(file_name, "r");
  if (file == NULL) {
    printf("\nUnable open file\n");
    exit(1);
  }
  while (fgets(buffer, sizeof(buffer), file)) {
    for (size_t col = 0; col < sizeof(buffer); col++) {
      if (buffer[col] == '|' || buffer[col] == '\n' || buffer[col] == '\t') {
        //printf("Continue: %zi | Row: %i\n", col, row);
        continue;
      }
      raw_level[row][col] = buffer[col];
    }
    row++;
  }
  if (row > ROWS) {
    fclose(file);
    exit(1);
  }
  fclose(file);
  return **raw_level;
}

void generate_level(const char *file_name, Tile parsed_level[ROWS][COLS],
                    Entity entity_list[ENTITY_TYPES][ENTITY_COUNT], Player *player)
{
  char raw_level[ROWS][COLS];
  load_file(file_name, raw_level);
  Texture fruit_texture = load_asset("../assets/fruit.png");
  int length;
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      switch (raw_level[r][c]) {
        case WALL:
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, GRAY, WALL};
          break;
        case FLOOR:
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, WHITE, FLOOR};
          break;
        case PLAYER:
          // Set the player spawn to a floor tile
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, WHITE, FLOOR};
          player->rect.x = TILE_SIZE * c;
          player->rect.y = TILE_SIZE * r;
          break;
        case EXIT:
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, BLUE, EXIT};
          break;
        case FRUIT:
          length = entityArrLength(entity_list[FRUIT_INT]);
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, WHITE, FLOOR};
          entity_list[FRUIT_INT][length] = (Entity){.type = FRUIT, .direction = STILL,
                                 .rect = {TILE_SIZE * c, TILE_SIZE *r, TILE_SIZE, TILE_SIZE},
                                 .texture=fruit_texture, .colour = DARKGREEN};
          break;
        case POWERUP:
          length = entityArrLength(entity_list[POWERUP_INT]);
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, WHITE, FLOOR};
          entity_list[POWERUP_INT][length] = (Entity){.type = POWERUP, .colour = PURPLE, .direction = STILL,
                                            .rect = {TILE_SIZE * c, TILE_SIZE *r, TILE_SIZE, TILE_SIZE}};
          break;
        case ENEMY:
          length = entityArrLength(entity_list[ENEMY_INT]);
          parsed_level[r][c] = (Tile){{TILE_SIZE * c, TILE_SIZE * r,
                                       TILE_SIZE, TILE_SIZE}, WHITE, FLOOR};
          entity_list[HUNTER][length] = (Entity){.type = ENEMY, .colour = RED, .direction = STILL,
                                            .rect = {TILE_SIZE * c, TILE_SIZE * r, TILE_SIZE, TILE_SIZE}};
          break;
        default:
          setEntity(raw_level[r][c], r, c, entity_list);
          break;
      }
    }
  }
}

