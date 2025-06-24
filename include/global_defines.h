#ifndef GLOBAL_DEFINES_
#define GLOBAL_DEFINES_

// General defines
#define BIG_FONT 60
#define MEDIUM_FONT 40
#define SMALL_FONT 20
#define WINDOWH 1024
#define WINDOWW 1024
#define GAME_TITLE "Cnake Man"

#define TEXTURE_SIZE 8 // Size of the texture
#define TEXTURE_SCALE TEXTURE_SIZE*4 // The scale of the texture used in the rectangle destination parameter

// Difficulties
#define EASY 1.0f
#define MEDIUM 0.64f
#define HARD 0.25f

// Level tile defines (types, size, how many)
#define WALL '#'
#define FLOOR '.'
#define TILE_SIZE 32
#define ROWS 32
#define COLS 32

// Player related defines
#define SNAKE_SIZE 32
#define STILL 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

// Array stuff
#define MAX_TEXTURES 32
#define MAX_PATH_LENGTH 32

#endif // !GAME_DEFINES_
