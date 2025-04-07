#ifndef CUSTOM_STRUCTS_
#define CUSTOM_STRUCTS_

#include "raylib.h"

// This is the player struct. It's just for the player head.
typedef struct Player {
  int direction; // 1: up, 2: right, 3: down, 4:left
  int powerup; // This will be used for special abilities
  int body_len;
  Rectangle rect;
} Player;

// This is used to generate the tiles of the levels.
// The .type matches the character used in the level.txt file.
//    walls -> #, hazard -> ^. Look in game_defines.h for each type.
typedef struct Tile {
  Rectangle rect;
  Color colour;
  char type;
} Tile;

// This struct is used for a lot of different things. From frutis to enemies.
// The snake_body is also an entity, except it's .type is set the player type.
typedef struct Entity {
  char type;
  Color colour;
  int direction;
  Rectangle rect;
  Texture texture;
} Entity;

#endif // !CUSTOM_STRUCTS_
