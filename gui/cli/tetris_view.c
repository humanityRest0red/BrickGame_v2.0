/**
 * @file tetris_view.c
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Implementation of functions for ncurses tetris view
 */

#include "tetris_view.h"

#include <unistd.h>

#include "curses_utils.h"

void GameLoop() {
  GameParams_t prms;
  InitializeParams(&prms);
  UpdateParams(&prms);

  double counter = 0;
  while (prms.info.pause != INFO_FINISH) {
    if (counter >= 10000) {
      DrawTetris(&prms);
      bool hold = false;
      UserAction_t action = GetAction(getch(), Down);
      userInput(action, hold);
      updateCurrentState();
      counter = 0;
    }
    counter += (double)prms.info.speed / 10000;
  }
  clear();
  DrawGameOver();
  refresh();
}

void DrawTetris(GameParams_t *prms) {
  erase();
  DrawGUI(TETRIS);
  DrawInfo(&prms->info);
  DrawNextTetromino(&prms->info, prms->tetromino.name_next + 1);
  DrawField(prms->info.field);
  DrawTetromino(&prms->tetromino);

  if (prms->info.pause == INFO_PAUSE) {
    DrawPause();
  }
}

void DrawNextTetromino(GameInfo_t *info, int color) {
  for (int i = 0; i < TETROMINO_HEIGHT; ++i) {
    for (int j = 0; j < TETROMINO_WIDTH; ++j) {
      attron(COLOR_PAIR(color));
      mvprintw(Y_NEXT + 4 + (i), BOARDS_BEGIN + (BOARD_M + 5 + j * 2 + 1),
               info->next[i][j] ? "[]" : "  ");
      attroff(COLOR_PAIR(color));
    }
  }
}

void DrawTetromino(Tetromino_t *tetromino) {
  if (tetromino->cells[0].y == 0 && tetromino->cells[0].x == 0) return;

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    DrawEntityCell(tetromino->cells[i].y, tetromino->cells[i].x,
                   tetromino->name + 1);
  }
}
