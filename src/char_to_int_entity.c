#include "char_to_int_entity.h"
#include "entity_defines.h"

int char_to_int_entity(char type) {
  switch(type) {
    case BODY:
      return PLAYER_INT;
    case BOUNCER_H:
      case BOUNCER_V:
      return BOUNCER;
    case PATROLLER_H:
      case PATROLLER_V:
      return PATROLLER;
    case HUNTER_H:
      case HUNTER_V:
      return HUNTER;
    default:
      return -1;
  }
}

