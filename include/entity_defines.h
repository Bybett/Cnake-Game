#ifndef ENTITY_DEFINES_
#define ENTITY_DEFINES_

#define ENTITY_TYPES 32
#define ENTITY_COUNT 32


// For parsing the level data from files
#define PLAYER '@'
#define PLAYER_INT 0
#define BODY '*'

#define HAZARD '&'
#define EXIT '^'

#define FRUIT '$'
#define FRUIT_INT 1

#define POWERUP '%'
#define POWERUP_INT 2

#define BOUNCER_V 'B' // Used for parsing the level data. Moves vertically
#define BOUNCER_H 'b' // Like previous line, but moves horizontal.
#define BOUNCER 3 // Used in the entity list array.

#define PATROLLER_V 'P'
#define PATROLLER_H 'p'
#define PATROLLER 4

#define HUNTER_V 'H'
#define HUNTER_H 'h'
#define HUNTER 5

#endif // !ENTITY_DEFINES_
