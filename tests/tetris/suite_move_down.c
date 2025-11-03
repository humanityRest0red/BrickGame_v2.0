#include "suitecases.h"

START_TEST(MoveDown_false_1) {
  // collide with field
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->info.field[15][1] = true;
  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = 14;
    prms->tetromino.cells[i].x = etalon.cells[i].x = i;
  }
  MoveDown(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }

  TerminateGame(prms);
}
END_TEST

START_TEST(MoveDown_false_2) {
  // collide with wall
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = HEIGHT - 1;
    prms->tetromino.cells[i].x = etalon.cells[i].x = i;
  }

  MoveDown(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }
  TerminateGame(prms);
}
END_TEST

START_TEST(MoveDown_true_1) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->info.field[15][1] = true;
  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = 14;
    prms->tetromino.cells[i].x = etalon.cells[i].x = i + 2;  // no 1
  }
  MoveDown(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y + 1);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }

  TerminateGame(prms);
}
END_TEST

START_TEST(MoveDown_true_2) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  Tetromino_t etalon;
  for (int i = 0; i < 3; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = HEIGHT - 2;
    prms->tetromino.cells[i].x = etalon.cells[i].x = WIDTH - 2 - i;
  }
  prms->tetromino.cells[3].y = etalon.cells[3].y = HEIGHT - 3;
  prms->tetromino.cells[3].x = etalon.cells[3].x = WIDTH - 3;

  MoveDown(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y + 1);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }
  TerminateGame(prms);
}
END_TEST

Suite* suite_MoveDown(void) {
  Suite* s = suite_create("MoveDown");
  TCase* tc = tcase_create("MoveDown");

  tcase_add_test(tc, MoveDown_false_1);
  tcase_add_test(tc, MoveDown_false_2);

  tcase_add_test(tc, MoveDown_true_1);
  tcase_add_test(tc, MoveDown_true_2);

  suite_add_tcase(s, tc);
  return s;
}
