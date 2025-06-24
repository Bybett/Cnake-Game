#include "asset_loader.h"
#include "global_structs.h"
#include "global_defines.h"
#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"

#define TEXTURE_MISSING 0
#define TEXTURE_SNAKE_HEAD 1
#define TEXTURE_BODY 2
#define TEXTURE_TAIL 3
#define TEXTURE_SLIM_BODY 4
#define TEXTURE_BODY_TURN 5
#define TEXTURE_FRUIT 6

void loadTextureArray(TextureStruct **texture_data) {
  // TODO: This whole thing is casuing problems lol. it is writing out of bounds, exactly like
  // the previous bug in snake_handler.c. Just gotta allocate it correctly and compare it
  // to the code in snake_handler.growSnake.

  const char *texture_paths[] = {
    "../assets/missing_texture.png",
    "../assets/snake_head.png", "../assets/body.png", "../assets/tail.png",
    "../assets/slim_body.png", "../assets/body_turn.png",
    "../assets/fruit.png"
  };

  const int texture_paths_count = sizeof(texture_paths) / sizeof(texture_paths[0]);
  (*texture_data)->array_length = texture_paths_count;

  // -Loop over texture_paths from texture_paths.h
  // -malloc a Texture pointer
  // -load the texture from the path into the pointer
  // -Set the texture_data->array to the malloc'd pointer
  for (int i = 0; i < texture_paths_count; i++) {
    Texture2D *load_texture = malloc(sizeof(Texture2D));
    *load_texture = LoadTexture(texture_paths[i]);
    (*texture_data)->array[i] = load_texture;
  }
}

