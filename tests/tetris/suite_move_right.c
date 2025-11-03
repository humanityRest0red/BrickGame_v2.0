#include "suitecases.h"

START_TEST(MoveRight_false_1) {
  // collide with field
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->info.field[15][WIDTH - 1] = true;
  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = 15;
    prms->tetromino.cells[i].x = etalon.cells[i].x = WIDTH - 2 - i;
  }
  MoveRight(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }

  TerminateGame(prms);
}
END_TEST

START_TEST(MoveRight_false_2) {
  // collide with wall
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = 15;
    prms->tetromino.cells[i].x = etalon.cells[i].x = WIDTH - 1 - i;
  }

  MoveRight(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }
  TerminateGame(prms);
}
END_TEST

START_TEST(MoveRight_true_1) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->info.field[15][WIDTH - 1] = true;
  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = 14;  // no 15
    prms->tetromino.cells[i].x = etalon.cells[i].x = WIDTH - 2 - i;
  }
  MoveRight(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x + 1);
  }

  TerminateGame(prms);
}
END_TEST

START_TEST(MoveRight_true_2) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  Tetromino_t etalon;
  for (int i = 0; i < 3; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = 15;
    prms->tetromino.cells[i].x = etalon.cells[i].x = WIDTH - 2 - i;
  }
  prms->tetromino.cells[3].y = etalon.cells[3].y = 14;
  prms->tetromino.cells[3].x = etalon.cells[3].x = WIDTH - 3;

  MoveRight(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x + 1);
  }
  TerminateGame(prms);
}
END_TEST

Suite* suite_MoveRight(void) {
  Suite* s = suite_create("MoveRight");
  TCase* tc = tcase_create("MoveRight");

  tcase_add_test(tc, MoveRight_false_1);
  tcase_add_test(tc, MoveRight_false_2);

  tcase_add_test(tc, MoveRight_true_1);
  tcase_add_test(tc, MoveRight_true_2);

  suite_add_tcase(s, tc);
  return s;
}
