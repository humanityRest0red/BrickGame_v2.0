#include "suitecases.h"

START_TEST(CanSpawn_true_1) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->info.field[1][2] = true;

  for (int j = 0; j < CELLS_IN_TETROMINO; ++j) {
    prms->info.next[1][j] = true;
  }
  ck_assert_int_eq(CanSpawn(prms), true);

  TerminateGame(prms);
}
END_TEST

START_TEST(CanSpawn_false_1) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  prms->info.field[1][3] = true;

  for (int j = 0; j < CELLS_IN_TETROMINO; ++j) {
    prms->info.next[1][j] = true;
  }
  ck_assert_int_eq(CanSpawn(prms), false);

  TerminateGame(prms);
}
END_TEST

Suite* suite_CanSpawn(void) {
  Suite* s = suite_create("CanSpawn");
  TCase* tc = tcase_create("CanSpawn");

  tcase_add_test(tc, CanSpawn_true_1);
  tcase_add_test(tc, CanSpawn_false_1);

  suite_add_tcase(s, tc);
  return s;
}
