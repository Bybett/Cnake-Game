#ifndef LEVEL_LOADER_
#define LEVEL_LOADER_

#include "global_structs.h"
#include "global_defines.h"
#include "entity_defines.h"

char load_file(const char*, char [ROWS][COLS]);

void generate_level(const char*, Tile[ROWS][COLS],
                    Entity[ENTITY_TYPES][ENTITY_COUNT], Player *player,
                    TextureStruct texture_data);

void print_level(Tile print_level[ROWS][COLS]);

#endif // LOAD_LEVEL_
