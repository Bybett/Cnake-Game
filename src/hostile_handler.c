#include "hostile_handler.h"
#include "entity_defines.h"
#include "raylib.h"
#include "move_entity.h"
#include "char_to_int_entity.h"
#include "global_defines.h"
#include "wall_collide.h"
#include "raylib.h"

void updateHostile(Entity *entity, Tile level[ROWS][COLS]) {
  int *direction = &entity->direction;
  int type = char_to_int_entity(entity->type);
//  int row = (int)(entity->rect.x / ROWS);
//  int col = (int)(entity->rect.y / COLS);
  Rectangle *rect = &entity->rect;
  Rectangle ghost = {rect->x, rect->y, TILE_SIZE, TILE_SIZE};

  // Move the point's x,y so that it is in front of the entity.
  moveEntity(&ghost, direction);
  //Since every entity will check if it collides with a wall, we could do it here.
  bool is_wall_collide = wallCollide(ghost, level);

  switch (type) {
    // Bouncer just inverts its direciton on wall collisions.
    case BOUNCER:
      if (is_wall_collide) {
        switch (*direction) {
          case UP:
            *direction = DOWN;
            break;
          case DOWN:
            *direction = UP;
            break;
          case LEFT:
            *direction = RIGHT;
            break;
          case RIGHT:
            *direction = LEFT;
            break;
        }
      }
      break;
    case PATROLLER:
      // The patroller will pace back and forth in an area through level design.
      // When the patroller bumps into a wall, it will check clock-wise which direction
      // it can move. It won't move backwards immediatly, it only will if there is
      // no other valid route for it.
      int backwards = 0;
      int initial_direction = *direction;
      // If the direction is either up or right, add 2 to make is the opposite dir.
      // If it's left or down, sub 2 to make it the opposite dir.
      if (*direction == UP || *direction == RIGHT) {
        backwards = *direction + 2;
      } else {
        backwards = *direction - 2;
      }

      // While the tile in the new spot is a wall, rotate around to find a valid route.
      // If we rotate 180, ignore that direction, we don't move backwards.
      // Continue rotating until we find a valid route.
      while (is_wall_collide) {
        // If current direction is LEFT, we need to set it to UP (left=4, up=1)
        if (*direction == LEFT) {
          *direction = UP;
        // As long as the direction is not pointing backwards, we rotate.
        } else {
          *direction = *direction + 1;
        }
        // Create a new ghost from the entity, move the ghost in the new direction.
        // Check if this new position is a wall, if it is, we continue the loop.
        ghost = (Rectangle){rect->x, rect->y, TILE_SIZE, TILE_SIZE};
        moveEntity(&ghost, direction);
        is_wall_collide = wallCollide(ghost, level);
        // We don't want to go backwards, unless there is no other valid route.
        if (!is_wall_collide && *direction == backwards) {
          is_wall_collide = true;
        }
        // If there are no valid, we go back the way we came.
        if (*direction == initial_direction) {
          is_wall_collide = false;
          *direction = backwards;
        }
      }
      break;
  }
  moveEntity(rect, direction);
}

