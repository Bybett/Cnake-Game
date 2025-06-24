#include "../include/raylib.h"
#include "../include/hostile_handler.h"
#include "../include/title_screen.h"
#include "../include/snake_handler.h"
#include "../include/level_loader.h"
#include "../include/arr_length.h"
#include "../include/asset_loader.h"
#include "../include/entity_defines.h"
#include "../include/global_defines.h"
#include "../include/global_structs.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN 0
#define LOSE 1
#define S_SCORE 10
#define B_SCORE 100

//--------------------------------
// Global variables
//--------------------------------

Player player = {.direction = RIGHT, .powerup = 0, .body_len = 2,
                 .rect = {0, 0, SNAKE_SIZE, SNAKE_SIZE}};
Entity fruit;

/*
 * Entities[][]
 *
 * Index 0, fruits
 * Index 1, powerups
 * Index 2, enemies
 */
Entity entities[ENTITY_TYPES][ENTITY_COUNT];
Tile level[ROWS][COLS];
Entity *snake_body;

int total_score = 0;
int level_score = 0;
bool restart;

// Setup for the texture_data object. This will store the paths, count, and pointers for
// all the textures used in the game.
TextureStruct *texture_data;


char levels_list[4][32] = {"../levels/level1.txt", "..levels/level2.txt"};

/* gameOver()
 *
 * This function is for executing the game over screen, whether it's a win
 * or lose situation. It's stop the game and draws text befiting
 * the situation.
 *
 * Params:
 *    int end_state -> win = 0, lose = 1
 *    There are #defines for win/lose
 */
void gameOver(int end_state) {
  if (!end_state) {
    BeginDrawing();
    ClearBackground(BLACK);
    int text_width = MeasureText("YOU WIN", BIG_FONT);
    DrawText("YOU WIN", WINDOWW / 2 - text_width / 2, WINDOWH / 3,
              BIG_FONT, GREEN);
    ClearBackground(BLACK);
  } else {
    BeginDrawing();
    ClearBackground(BLACK);
    int text_width = MeasureText("GAME OVER", BIG_FONT);
    DrawText("GAME OVER", WINDOWW / 2 - text_width / 2, WINDOWH / 3,
              BIG_FONT, RED);
  }
  EndDrawing();
  WaitTime(2);
  CloseWindow();
  free(snake_body);
  exit(0);
}

/* displayUI()
 *
 * This guy is for displaying the current level score (some levels need a 
 * certain score to continue), displaying the global score
 * (total score across all levels), and the length of the snake (some levels
 * will need the player to long enough to continue).
 *
 * Params:
 *    int level_s -> level score
 *    int total_s -> total game score
 */
void displayUI(int level_s, int total_s) {
  //int level_s_width = MeasureText(level_s, SMALL_FONT);
  //int total_s_width = MeasureText(total_s, SMALL_FONT);
  DrawText(TextFormat("Score: %i", level_s), 10, 10, SMALL_FONT, BLACK);
  DrawText(TextFormat("Game Score: %i", total_s), 200, 10, SMALL_FONT, BLACK);
}

/* respawnEntity()
 *
 * This cheeki function is used to respawn various types of entities.
 * From the humble fruit to the hostile enemy, this function will respawn it.
 *
 * Params:
 *    Entity entity   -> the entity obj to respawn
 *    Tile valid_tile -> the tiles that the entity can spawn on.
 */
void respawnEntity(Entity *re_entity, char valid_tile) {
  int x_rand = GetRandomValue(0, COLS);
  int y_rand = GetRandomValue(0, ROWS);
  while (level[x_rand][y_rand].type != valid_tile) {
    x_rand = GetRandomValue(0, COLS);
    y_rand = GetRandomValue(0, ROWS);
  }
  re_entity->rect.x = level[x_rand][y_rand].rect.x;
  re_entity->rect.y = level[x_rand][y_rand].rect.y;
}

/* eventHandler()
 *
 * This lil guy is for checking any game events. Player inputs, collision,
 * enemy attacks, spawning objects, and etc, is all done in here.
 *
 * Params:
 *    None
 */
void eventHandler() {
  // Check user input here
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
    player.direction = UP;
  } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
    player.direction = DOWN;
  } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
    player.direction = LEFT;
  } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
    player.direction = RIGHT;
  }

  int player_row, player_col;
  // Little trick. Since the pos is a multiple of the row/col and TILE_SIZE,
  // just divide by TILE_SIZE to get the row/col
  player_row = player.rect.y / TILE_SIZE;
  player_col = player.rect.x / TILE_SIZE;
  Tile current_tile = level[player_row][player_col];
  if (CheckCollisionRecs(player.rect, current_tile.rect)) {
    switch (current_tile.type) {
      case WALL:
        gameOver(LOSE);
        break;
      case PLAYER:
        gameOver(LOSE);
        break;
      case EXIT:
        gameOver(WIN);
        break;
    }
  }
}


/*
 * This handles all the collision detection for when the player collides with an entity
 */
void entityPlayerCollision() {
  // Checking for player collision with various entities.
  // Can't do the row/col divide by TILE_SIZE trick because we have to check
  // a variable amount of entities
  for (int r = 0; r < ENTITY_TYPES; r++) {
    for (int c = 0; c < ENTITY_COUNT; c++) {
      Entity currenty_entity = entities[r][c];
      if (CheckCollisionRecs(player.rect, currenty_entity.rect)) {
        switch (currenty_entity.type) {
          case FRUIT:
            total_score += S_SCORE;
            level_score += S_SCORE;
            respawnEntity(&entities[r][c], FLOOR);
            growSnake(&player, &snake_body, *texture_data);
            break;
          case POWERUP:
            total_score += B_SCORE;
            level_score += B_SCORE;
            respawnEntity(&entities[r][c], FLOOR);
            break;
          case HAZARD:
            shrinkSnake(&player, &snake_body, *texture_data);
            break;
          case BOUNCER:
            shrinkSnake(&player, &snake_body, *texture_data);
            break;
          case BOUNCER_V:
            shrinkSnake(&player, &snake_body, *texture_data);
            break;
        }
        if (player.body_len == 0) {
          gameOver(LOSE);
          free(snake_body);
          CloseWindow();
          exit(0);
        }
      }
    }
    for (int i = 1; i < player.body_len; i++) {
      if (CheckCollisionRecs(player.rect, snake_body[i].rect) && snake_body[i].type == BODY) {
        gameOver(LOSE);
      }
    }
  }
}

void entityBodyCollision() {
  for (int t = 0; t < ENTITY_TYPES; t++) {
    for (int c = 0; c < ENTITY_COUNT; c++) {
      for (int i = 0; i < player.body_len; i++) {
        if (CheckCollisionRecs(snake_body[i].rect, entities[t][c].rect)) {
          shrinkSnake(&player, &snake_body, *texture_data);
            if (player.body_len == 0) {
            gameOver(LOSE);
          }
        }
        if (CheckCollisionRecs(snake_body[0].rect, player.rect)) {
          gameOver(LOSE);
        }
      }
    }
  }
}

/* updateGame()
 *
 * This function updates any logic or states. Entities moving, player movement,
 * checking animations (if I do any).
 *
 * Params:
 *    None
 */
void updateGame() {
  int length = player.body_len - 1;

  // Shift each body segment to the next position to make the body follow the player.
  for (int b = length; b > 0; b--) {
    snake_body[b].rect = snake_body[b - 1].rect;
  }
  snake_body[0].rect = player.rect;

  // Move the player depending on the value of player.direction
  switch (player.direction) {
    case UP:
      player.rect.y -= TILE_SIZE;
      break;
    case DOWN:
      player.rect.y += TILE_SIZE;
      break;
    case LEFT:
      player.rect.x -= TILE_SIZE;
      break;
    case RIGHT:
      player.rect.x += TILE_SIZE;
      break;
  }

  // Checks if the player escapes the screen... somehow :shrug:
  if (player.rect.y < 0 || player.rect.y > WINDOWH) {
    gameOver(LOSE);
  } else if (player.rect.x < 0 || player.rect.x > WINDOWW) {
    gameOver(LOSE);
  }

  // Loop over entities and update their current pos
  for (int type = 0; type < ENTITY_TYPES; type++) {
    int hostile_count = entityArrLength(entities[type]);
    for (int count = 0; count < hostile_count; count++) {
      Entity *hostile = &entities[type][count];
      updateHostile(hostile, level);
    }
  }
}

/* initGame()
 *
 * This function is one of the first blocks of code executed
 * when the game starts. It loads the initial level from ./levels,
 * it sets the player to their starting position, spawns the first
 * set of fruits, powerups, hazards, enemies, etc.
 *
 * Params:
 *    None
 */
void initGame(Entity **body) {
  // Load le textures into HEAP!!
  texture_data = malloc(sizeof(TextureStruct));
  loadTextureArray(&texture_data);

  // First arg is the level file, second arg is where to store the data.
  generate_level(levels_list[0], level, entities, &player, *texture_data);

  *body = malloc(sizeof(Entity) * player.body_len);

  if (*body == NULL) {
    printf("Error malloc'ing snake body\n");
    exit(1);
  }

  setSnake(&snake_body, *texture_data);
}

/* main()
 *
 * The window is initialized here, the logic functions are called here, and
 * the game doing its thing is going on here.
 *
 * Params:
 *    None
 */
int main() {
  InitWindow(WINDOWW, WINDOWH, "Cnake Man");

  float difficulty = EASY;
  float previous_time = 0.0f;
  initGame(&snake_body);

  SetTargetFPS(60);
  displayTitleScreen(&difficulty);
  while (!WindowShouldClose()) {
    float current_time = GetTime();
    BeginDrawing();
    ClearBackground(WHITE);

    // Only update game logic once every wait_time.
    // Get entities to move one tile/s
    if (current_time - previous_time >= difficulty) {
      previous_time = GetTime();
      updateGame();
      entityPlayerCollision();
      entityBodyCollision();
    }

    eventHandler();

    // Render the level
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLS; c++) {
        DrawRectangleRec(level[r][c].rect, level[r][c].colour);
      }
    }

    // Render all the entities
    for (int t = 0; t < ENTITY_TYPES; t++) {
      int count = entityArrLength(entities[t]);
      for (int c = 0; c < count; c++) {
        Entity entity = entities[t][c];
        // If the entity doesn't have a texture, draw a basic rect with a colour.
        if (entity.texture.id == (unsigned)0) {
          DrawRectangleRec(entity.rect, entity.colour);
        // If the entity does have a texture, draw it.
        } else if (entity.texture.id > (unsigned)0) {
          DrawTexturePro(entity.texture,
                        (Rectangle){0, 0, TEXTURE_SIZE, TEXTURE_SIZE},  // Source texture. Defines what part of the texture to draw
                        (Rectangle){entity.rect.x, entity.rect.y, TEXTURE_SCALE, TEXTURE_SCALE},  // Destination. Where and how big the texture is.
                        (Vector2){0, 0}, 0, WHITE);
        } else {
          printf("ERROR DRAWING ENTITY: NO COLOUR OR TEXTURE");
        }
      }
    }

    // Render the snake_body
    for (int s = 0; s < player.body_len; s++) {
      Entity segment = snake_body[s];
      DrawTexturePro(segment.texture,
                  (Rectangle){0, 0, TEXTURE_SIZE, TEXTURE_SIZE},
                  (Rectangle){segment.rect.x, segment.rect.y, TEXTURE_SCALE, TEXTURE_SCALE},
                  (Vector2){0,0}, 0, WHITE);
    }

    // Draw the player
    DrawTexturePro(player.texture,
                  (Rectangle){0, 0, TEXTURE_SIZE, TEXTURE_SIZE},
                  (Rectangle){player.rect.x, player.rect.y, TEXTURE_SCALE, TEXTURE_SCALE},
                  (Vector2){0,0}, 0, WHITE);
    displayUI(level_score, total_score);  // This is always rendered last
    EndDrawing();
  }

  free(snake_body);
  CloseWindow();
  exit(0);
}

