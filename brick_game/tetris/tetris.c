/**
 * @file tetris.c
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Implementation of functions for tetris game
 */

#include "tetris.h"

#include <stdlib.h>
#include <time.h>

GameInfo_t updateCurrentState(void) {
  GameParams_t *prms = UpdateParams(NULL);
  return prms->info;
}

void userInput(UserAction_t action, bool hold) {
  static const ActionT fsmTable[4][8] = {
      {StartGame, NULL, TerminateGame, NULL, NULL, NULL, NULL, NULL},
      {MoveDown, PauseGame, TerminateGame, MoveLeft, MoveRight, NULL, MoveDown,
       Rotate},
      {NULL, PauseGame, TerminateGame, NULL, NULL, NULL, NULL, NULL},
      {NULL, NULL, TerminateGame, NULL, NULL, NULL, NULL, NULL}};

  GameParams_t *prms = UpdateParams(NULL);
  ActionT func = fsmTable[prms->info.pause][action];
  if (func) {
    if (action == Down && hold) {
      for (Coord_t i = 0; i < HEIGHT; ++i) {
        func(prms);
      }
    } else {
      func(prms);
    }
  }
}

GameParams_t *UpdateParams(GameParams_t *params) {
  static GameParams_t *data;
  if (params != NULL) data = params;
  return data;
}

void InitializeParams(GameParams_t *prms) {
  prms->info = InitInfo(TETRIS_HIGH_SCORE_FILE_NAME);
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = 0;
    prms->tetromino.cells[i].x = 0;
  }
  srand(time(NULL));
  prms->tetromino.name_next = rand() % 7;
}

void Spawn(GameParams_t *prms) {
  static const Tetromino_t tetrominoes[] = {
      [I].cells = {{0, 1}, {1, 1}, {2, 1}, {3, 1}},   // ....
      [J].cells = {{0, 0}, {0, 1}, {1, 1}, {2, 1}},   // :..
      [L].cells = {{2, 0}, {0, 1}, {1, 1}, {2, 1}},   // ..:
      [O].cells = {{1, 0}, {2, 0}, {1, 1}, {2, 1}},   //  ::
      [S].cells = {{1, 0}, {2, 0}, {0, 1}, {1, 1}},   // .:'
      [T].cells = {{1, 0}, {0, 1}, {1, 1}, {2, 1}},   // .:.
      [Z].cells = {{0, 0}, {1, 0}, {1, 1}, {2, 1}}};  // ':.

  int8_t name_now = prms->tetromino.name_next;
  prms->tetromino.name = name_now;

  const Cell_t *cells = tetrominoes[name_now].cells;
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].x = WIDTH / 2 - 2 + cells[i].x;
    prms->tetromino.cells[i].y = cells[i].y;
  }

  prms->tetromino.name_next = rand() % 7;

  for (Coord_t i = 0; i < TETROMINO_HEIGHT; ++i) {
    for (Coord_t j = 0; j < TETROMINO_WIDTH; ++j) {
      prms->info.next[i][j] = 0;
    }
  }

  const Tetromino_t next = tetrominoes[prms->tetromino.name_next];
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->info.next[next.cells[i].y][next.cells[i].x] = 1;
  }
}

void StartGame(GameParams_t *prms) {
  prms->info.pause = INFO_START;
  Spawn(prms);
}

void PauseGame(GameParams_t *prms) {
  prms->info.pause = prms->info.pause == INFO_PAUSE ? INFO_START : INFO_PAUSE;
}

void TerminateGame(GameParams_t *prms) {
  RemoveInfo(&prms->info, TETRIS_HIGH_SCORE_FILE_NAME);
  prms->info.pause = INFO_FINISH;
}

void MoveDown(GameParams_t *prms) {
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) prms->tetromino.cells[i].y++;
  if (IsAttach(prms)) {
    Attach(prms);
  } else if (IsCollide(prms)) {
    for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i)
      prms->tetromino.cells[i].y--;
  }
}

void MoveRight(GameParams_t *prms) {
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) prms->tetromino.cells[i].x++;
  if (IsCollide(prms)) {
    for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i)
      prms->tetromino.cells[i].x--;
  }
}

void MoveLeft(GameParams_t *prms) {
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) prms->tetromino.cells[i].x--;
  if (IsCollide(prms)) {
    for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i)
      prms->tetromino.cells[i].x++;
  }
}

void Rotate(GameParams_t *prms) {
  // if figure is not square
  if (prms->tetromino.name != O) {
    Cell_t center;
    switch (prms->tetromino.name) {
      case I:
      case Z:
        center = prms->tetromino.cells[1];
        break;
      case J:
      case L:
        center = prms->tetromino.cells[2];
        break;
      default:
        center = prms->tetromino.cells[0];
        break;
    }

    Tetromino_t temp;
    for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
      temp.cells[i].x = prms->tetromino.cells[i].x;
      temp.cells[i].y = prms->tetromino.cells[i].y;
    }

    for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
      prms->tetromino.cells[i].x = center.x + center.y - temp.cells[i].y;
      prms->tetromino.cells[i].y = center.y - center.x + temp.cells[i].x;
    }

    if (IsCollide(prms))
      for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i)
        prms->tetromino.cells[i] = temp.cells[i];
  }
}

bool IsCollide(GameParams_t *prms) {
  bool check = false;
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO && !check; ++i) {
    if (prms->tetromino.cells[i].x < 0 || prms->tetromino.cells[i].x >= WIDTH ||
        prms->tetromino.cells[i].y < 0 ||
        prms->tetromino.cells[i].y >= HEIGHT ||
        prms->info
            .field[prms->tetromino.cells[i].y][prms->tetromino.cells[i].x])
      check = true;
  }

  return check;
}

bool IsAttach(GameParams_t *prms) {
  bool check = false;
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO && !check; ++i)
    if (prms->tetromino.cells[i].y == HEIGHT - 1 ||
        prms->info
            .field[prms->tetromino.cells[i].y + 1][prms->tetromino.cells[i].x])
      check = true;

  return check;
}

void Attach(GameParams_t *prms) {
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->info.field[prms->tetromino.cells[i].y][prms->tetromino.cells[i].x] =
        prms->tetromino.name + 1;
  }

  static const unsigned scores[5] = {0, 100, 300, 700, 1500};
  prms->info.score += scores[LinesDisappeared(prms->info.field)];
  while (prms->info.score >= prms->info.level * 600 && prms->info.level < 10) {
    ++prms->info.level;
  }
  prms->info.speed = prms->info.level;
  CanSpawn(&prms->info) ? Spawn(prms) : TerminateGame(prms);
}

Coord_t LinesDisappeared(int **field) {
  Coord_t result = 0;
  for (Coord_t i = 0; i < HEIGHT; ++i) {
    bool check = true;
    for (Coord_t j = 0; j < WIDTH && check; ++j) {
      if (!field[i][j]) check = false;
    }
    if (check) {
      ++result;
      for (Coord_t ind = i; ind >= 1; --ind) {
        for (Coord_t j = 0; j < WIDTH; ++j) {
          field[ind][j] = field[ind - 1][j];
        }
      }
    }
  }
  return result;
}

bool CanSpawn(const GameInfo_t *info) {
  bool check = true;
  for (Coord_t i = 0; i < TETROMINO_HEIGHT && check; ++i) {
    for (Coord_t j = 0; j < TETROMINO_WIDTH && check; ++j) {
      if (info->next[i][j] && info->field[i][j + (WIDTH / 2 - 2)])
        check = false;
    }
  }

  return check;
}
