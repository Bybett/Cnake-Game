#ifndef ASSET_LOADER_
#define ASSET_LOADER_

#include "global_structs.h"

#define TEXTURE_MISSING 0
#define TEXTURE_SNAKE_HEAD 1
#define TEXTURE_BODY 2
#define TEXTURE_TAIL 3
#define TEXTURE_SLIM_BODY 4
#define TEXTURE_BODY_TURN 5
#define TEXTURE_FRUIT 6

void loadTextureArray(TextureStruct **texture_data);

#endif
