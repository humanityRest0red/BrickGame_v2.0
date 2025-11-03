#include "suitecases.h"

START_TEST(test_InitializePrms) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  ck_assert_int_eq(prms->info.pause, false);
  ck_assert_ptr_nonnull(prms->info.field);
  ck_assert_ptr_nonnull(prms->info.next);
  ck_assert_int_eq(prms->info.level, 1);
  ck_assert_int_eq(prms->info.speed, 1);
  ck_assert_int_eq(prms->info.score, 0);
  ck_assert_int_eq(prms->state, START);

  TerminateGame(prms);
}
END_TEST

START_TEST(test_StartGame) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  StartGame(prms);
  ck_assert_int_eq(prms->state, SPAWN);

  TerminateGame(prms);
}
END_TEST

START_TEST(test_PauseGame) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  ck_assert_int_eq(prms->info.pause, false);
  PauseGame(prms);
  ck_assert_int_eq(prms->info.pause, true);
  PauseGame(prms);
  ck_assert_int_eq(prms->info.pause, false);

  TerminateGame(prms);
}
END_TEST

START_TEST(test_Spawn) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  Spawn(prms);
  ck_assert_int_eq(prms->state, MOVING);

  TerminateGame(prms);
}
END_TEST

START_TEST(test_WriteHighScore) {
  GameParams_t params;
  GameParams_t* prms = &params;
  InitializeParams(prms);

  int old_high_score = ReadHighScore(TETRIS_HIGH_SCORE_FILE_NAME);
  prms->info.score = old_high_score + 100;
  Attach(prms);
  ck_assert_int_eq(prms->info.score,
                   ReadHighScore(TETRIS_HIGH_SCORE_FILE_NAME));
  WriteHighScore(TETRIS_HIGH_SCORE_FILE_NAME, old_high_score);

  TerminateGame(prms);
}
END_TEST

Suite* suite_minor_tests() {
  Suite* s = suite_create("minor_tests");
  TCase* tc = tcase_create("minor_tests");

  tcase_add_test(tc, test_InitializePrms);
  tcase_add_test(tc, test_StartGame);
  tcase_add_test(tc, test_PauseGame);
  tcase_add_test(tc, test_Spawn);
  tcase_add_test(tc, test_WriteHighScore);

  suite_add_tcase(s, tc);
  return s;
}
