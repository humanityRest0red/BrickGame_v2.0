#include <check.h>

#include "suitecases.h"

int main(void) {
  run_tests();
  return 0;
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;
  if (counter_testcase > 1) counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests(void) {
  Suite *list_cases[] = {
      suite_MoveDown(),  suite_MoveRight(),   suite_MoveLeft(),
      suite_Shift(),     suite_Rotate(),

      suite_IsCollide(), suite_IsAttach(),    suite_LinesDisappeared(),
      suite_CanSpawn(),  suite_minor_tests(), NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}
