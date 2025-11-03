#ifndef TESTS_SUITECASES_H_
#define TESTS_SUITECASES_H_

#include <check.h>

#include "tetris.h"

Suite *suite_MoveDown(void);
Suite *suite_MoveRight(void);
Suite *suite_MoveLeft(void);
Suite *suite_Shift(void);
Suite *suite_Rotate(void);

Suite *suite_IsCollide(void);
Suite *suite_IsAttach(void);
Suite *suite_LinesDisappeared(void);
Suite *suite_CanSpawn(void);

Suite *suite_minor_tests(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // TESTS_SUITECASES_H_
