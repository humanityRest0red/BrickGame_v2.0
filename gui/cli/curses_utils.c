/**
 * @file curses_utils.c
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Implementation of functions for ncurses tetris view
 */

#include "curses_utils.h"

void WinInit() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, 1);
  halfdelay(0);
  start_color();
  int COLOR_ORANGE = 8;
  int GRAY = 9;
  init_color(COLOR_ORANGE, 1000, 670, 0);
  init_color(GRAY, 192, 192, 192);
  // init_pair(0, GRAY, COLOR_GRAY);
  int COLOR_BG = COLOR_BLACK;
  init_pair(0, COLOR_WHITE, COLOR_BG);
  init_pair(1, COLOR_CYAN, COLOR_BG);
  init_pair(2, COLOR_BLUE, COLOR_BG);
  init_pair(3, COLOR_ORANGE, COLOR_BG);
  init_pair(4, COLOR_YELLOW, COLOR_BG);
  init_pair(5, COLOR_GREEN, COLOR_BG);
  init_pair(6, COLOR_MAGENTA, COLOR_BG);
  init_pair(7, COLOR_RED, COLOR_BG);
  bkgd(COLOR_PAIR(0));
}

UserAction_t GetAction(int user_input, UserAction_t default_action) {
  UserAction_t action = default_action;
  if (user_input == ENTER_KEY)
    action = Start;
  else if (user_input == PAUSE_KEY)
    action = Pause;
  else if (user_input == ESCAPE_KEY)
    action = Terminate;
  else if (user_input == KEY_LEFT)
    action = Left;
  else if (user_input == KEY_RIGHT)
    action = Right;
  else if (user_input == KEY_UP)
    action = Up;
  else if (user_input == KEY_DOWN)
    action = Down;
  else if (user_input == ACTION_KEY)
    action = Action;
  return action;
}

void DrawGUI(Game_t game) {
  DrawRectangle(0, BOARD_N + 1, 0, BOARD_M + 1);
  DrawRectangle(0, BOARD_N + 1, BOARD_M + 1, BOARD_M + HUD_WIDTH + 1);

  DrawRectangle(Y_NEXT - 1, Y_NEXT + 5, BOARD_M + 3, BOARD_M + HUD_WIDTH);
  DrawRectangle(Y_SCORE - 1, Y_SCORE + 3, BOARD_M + 3, BOARD_M + HUD_WIDTH);
  DrawRectangle(Y_HIGH_SCORE - 1, Y_HIGH_SCORE + 3, BOARD_M + 3,
                BOARD_M + HUD_WIDTH);
  DrawRectangle(Y_LEVEL - 1, Y_LEVEL + 1, BOARD_M + 3, BOARD_M + HUD_WIDTH);

  DRAW_ON_BOARD(Y_NEXT, BOARD_M + 8, "Next");
  DRAW_ON_BOARD(Y_SCORE, BOARD_M + 7, "Score");
  DRAW_ON_BOARD(Y_HIGH_SCORE, BOARD_M + 5, "High score");
  DRAW_ON_BOARD(Y_LEVEL, BOARD_M + 5, "Level");

  // DRAW_ON_BOARD(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1,
  //               INTRO_MESSAGE);
  // int color = 1;
  // attron(COLOR_PAIR(color));
  mvprintw(2, X_INSTRUCTIONS, "ENTER - Start");
  mvprintw(3, X_INSTRUCTIONS, "KEYS <%s v > - Move",
           game == TETRIS ? "" : " ^");
  mvprintw(4, X_INSTRUCTIONS, "SPACE - %s",
           game == TETRIS ? "Rotate" : "Speed UP");
  mvprintw(5, X_INSTRUCTIONS, "P - Pause");
  mvprintw(6, X_INSTRUCTIONS, "ESC - Quite");
  // attroff(COLOR_PAIR(color));
}

void DrawRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; ++i) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (i = top_y + 1; i < bottom_y; ++i) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; ++i) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void DrawInfo(GameInfo_t *info) {
  DRAW_ON_BOARD(Y_SCORE + 2, BOARD_M + 10, "%d", info->score);
  DRAW_ON_BOARD(Y_HIGH_SCORE + 2, BOARD_M + 10, "%d", info->high_score);
  DRAW_ON_BOARD(Y_LEVEL, BOARD_M + 12, "%d", info->level);
}

void DrawField(int **field) {
  for (uint8_t i = 0; i < HEIGHT; ++i)
    for (uint8_t j = 0; j < WIDTH; ++j)
      if (field[i][j]) DrawEntityCell(i, j, field[i][j]);
      // else DrawEntityCell(i, j, 0);
      else {
        int color = 0;
        attron(COLOR_PAIR(color));
        mvprintw(1 + BOARDS_BEGIN + (i), BOARDS_BEGIN + (j * 2 + 1), "  ");
        attron(COLOR_PAIR(color));
      }
}

void DrawEntityCell(uint8_t i, uint8_t j, int8_t color) {
  attron(COLOR_PAIR(color));
  mvprintw(1 + BOARDS_BEGIN + (i), BOARDS_BEGIN + (j * 2 + 1), "[]");
  attroff(COLOR_PAIR(color));
}

void DrawPause() { mvprintw(1 + BOARD_M / 2, BOARD_N / 2, "PAUSE"); }

void DrawGameOver() {
  int8_t color = 7;
  attron(COLOR_PAIR(color));
  mvprintw(9, X_INSTRUCTIONS, "GAME OVER");
  attroff(COLOR_PAIR(color));

  mvprintw(12, X_INSTRUCTIONS - 5, "Press Enter to quit");
}
