#ifndef SET_ENTITY_
#define SET_ENTITY_

#include "entity_defines.h"
#include "global_structs.h"

void setEntity(char type, int row, int col, Entity list[ENTITY_TYPES][ENTITY_COUNT],
               TextureStruct texture_data);

#endif // !SET_ENTITY_
