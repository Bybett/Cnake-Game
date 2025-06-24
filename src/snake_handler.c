#include "snake_handler.h"
#include "global_structs.h"
#include "raylib.h"
#include "entity_defines.h"
#include "asset_loader.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// Talking about double pointers:
// So, double pointers are simple a "pointer that points to another pointer."
// We will call the pointer being stored the "child" and the one storing the child the "parent."
//    Parents > child > array
// The parent here is allowing us to rewrite the address of the child with a new one.
// For example, the child is pointing to an array on the heap. When we want to expand or shrink
// the array using realloc(), we get a new pointer from realloc(), so we need to assign this new
// pointer to the child using the parent.
void growSnake(Player *player, Entity **body, TextureStruct texture_data) {
  Texture tail_texture = *texture_data.array[TEXTURE_TAIL];
  Texture body_texture = *texture_data.array[TEXTURE_BODY];
  int new_length = player->body_len + 1;
  Entity *new_body = realloc(*body, sizeof(Entity) * new_length);

  if (new_body == NULL) {
    printf("Error growing snake! -> snake_handler.c");
    free(*body);
    CloseWindow();
    exit(1);
  }

  // new_length is in human numbers (counts from 1). array_index is for compters
  int array_index = new_length - 1;
  *body = new_body;

  (*body)[array_index].type = BODY;
  (*body)[array_index].colour = GREEN;
  (*body)[array_index].texture = tail_texture;

  // Since the old tail is now a body segment, we need to set its texture from the tail.png,
  // to the body.png. But, we only do that if there is more than one segment.
  if (new_length > 1) {
    (*body)[array_index - 1].texture = body_texture;
    (*body)[array_index].rect = (*body)[array_index - 1].rect;
  }

  (*player).body_len++;
}

void shrinkSnake(Player *player, Entity **body, TextureStruct texture_data) {
  int new_length = player->body_len - 1;

  if (new_length <= 0) {
    player->body_len = 0;
    return;
  }

  Entity *new_body = realloc(*body, sizeof(Entity) * new_length);

  if (new_body == NULL) {
    printf("Error shrinking body! -> snake_handler.c");
    free(*body);
    CloseWindow();
    exit(1);
  }

  *body = new_body;
  player->body_len--;
}

// We don't need to set the player here, as it is set during level loading
void setSnake(Entity **body, TextureStruct texture_data) {
  (*body)[0].texture = *texture_data.array[TEXTURE_BODY];
  (*body)[1].texture = *texture_data.array[TEXTURE_TAIL];
}

