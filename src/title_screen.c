#include "title_screen.h"
#include "ui_element.h"
#include "global_defines.h"
#include "raylib.h"
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>

void displayTitleScreen(float *difficulty) {
  int window_width = WINDOWW / 2;
  int window_height= WINDOWH / 8 ;
  int text_width = MeasureText(GAME_TITLE, BIG_FONT);
  UI_Element easy_element = define_element("1-EASY", MEDIUM_FONT, (Vector2){.x=window_width, .y=window_height * 2});
  UI_Element medium_element = define_element("2-MEDIUM", MEDIUM_FONT, (Vector2){.x=window_width, .y=window_height * 3});
  UI_Element hard_element = define_element("3-HARD", MEDIUM_FONT, (Vector2){.x=window_width, .y=window_height * 4});
  UI_Element move_instructions = define_element("WASD/ARROWS TO MOVE", SMALL_FONT, (Vector2){.x=window_width, .y= window_height * 7});
  UI_Element objectives = define_element("COLLECT FRUIT. AVOID ENEMIES.", SMALL_FONT, (Vector2){.x=window_width, .y=window_height * 7.5});

  while (true) {
    if (WindowShouldClose()) {CloseWindow(); exit(0);};
    if (IsKeyPressed(KEY_ONE)) {
      *difficulty = EASY;
      break;
    } else if (IsKeyPressed(KEY_TWO)) {
      *difficulty = MEDIUM;
      break;
    } else if (IsKeyPressed(KEY_THREE)) {
      *difficulty = HARD;
      break;
    }

    BeginDrawing();

    ClearBackground(WHITE);
    DrawText(GAME_TITLE, WINDOWW / 2 - text_width / 2, 120, BIG_FONT, GREEN);
    drawUIElement(&easy_element, false);
    drawUIElement(&medium_element, false);
    drawUIElement(&hard_element, false);
    drawUIElement(&move_instructions, false);
    drawUIElement(&objectives, false);

    EndDrawing();
  }
}

