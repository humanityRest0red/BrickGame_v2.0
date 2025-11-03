#include "suitecases.h"

START_TEST(rotate_false_1) {
  // collide with left wall
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  Tetromino_t etalon;
  prms->tetromino.name = I;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    prms->tetromino.cells[i].y = etalon.cells[i].y = i;
    prms->tetromino.cells[i].x = etalon.cells[i].x = 0;
  }
  Rotate(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }

  TerminateGame(prms);
}
END_TEST

START_TEST(rotate_true_1) {
  // Rotate  square ::
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->tetromino.name_next = O;
  Spawn(prms);

  Tetromino_t etalon;
  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    etalon.cells[i].y = prms->tetromino.cells[i].y;
    etalon.cells[i].x = prms->tetromino.cells[i].x;
  }
  Rotate(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }

  TerminateGame(prms);
}
END_TEST

START_TEST(rotate_true_2) {
  // Rotate  J :.. //
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->tetromino.name_next = J;
  Spawn(prms);

  prms->tetromino.cells[0].y = 3;
  prms->tetromino.cells[0].x = 3;
  prms->tetromino.cells[1].y = 4;
  prms->tetromino.cells[1].x = 3;
  prms->tetromino.cells[2].y = 4;
  prms->tetromino.cells[2].x = 4;
  prms->tetromino.cells[3].y = 5;
  prms->tetromino.cells[3].x = 4;

  Tetromino_t etalon;
  etalon.cells[0].y = 3;
  etalon.cells[0].x = 5;
  etalon.cells[1].y = 3;
  etalon.cells[1].x = 4;
  etalon.cells[2].y = 4;
  etalon.cells[2].x = 4;
  etalon.cells[3].y = 4;
  etalon.cells[3].x = 3;

  Rotate(prms);

  for (int i = 0; i < CELLS_IN_TETROMINO; ++i) {
    ck_assert_int_eq(prms->tetromino.cells[i].y, etalon.cells[i].y);
    ck_assert_int_eq(prms->tetromino.cells[i].x, etalon.cells[i].x);
  }

  TerminateGame(prms);
}
END_TEST

Suite* suite_Rotate(void) {
  Suite* s = suite_create("Rotate");
  TCase* tc = tcase_create("Rotate");

  tcase_add_test(tc, rotate_false_1);
  tcase_add_test(tc, rotate_true_1);
  tcase_add_test(tc, rotate_true_2);

  suite_add_tcase(s, tc);
  return s;
}
