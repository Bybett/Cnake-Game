#ifndef CUSTOM_STRUCTS_
#define CUSTOM_STRUCTS_

#include "raylib.h"
#include "global_defines.h"

// This is the player struct. It's just for the player head.
typedef struct Player {
  int direction; // 1: up, 2: right, 3: down, 4:left
  int powerup; // This will be used for special abilities
  int body_len;
  Rectangle rect;
  Texture2D texture;
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
// The snake_body is also an entity
typedef struct Entity {
  char type;
  Color colour;
  int direction;
  Rectangle rect;
  Texture2D texture;
} Entity;

typedef struct TextureStruct {
  char texture_paths[MAX_TEXTURES]; // An array storing all the texture paths
  Texture2D *array[MAX_TEXTURES]; // Another array storing all the textures in memory
  int array_length; // Used for tracking how many textures there are
} TextureStruct;

#endif // !CUSTOM_STRUCTS_
