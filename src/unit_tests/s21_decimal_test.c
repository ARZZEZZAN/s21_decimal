#include "s21_decimal_test.h"

void run_tests(void) {
  Suite *list_cases[] = {suite_add(),
                         suite_sub(),
                         suite_mul(),
                         suite_mod(),
                         suite_div(),

                         suite_is_less(),
                         suite_is_less_or_equal(),
                         suite_is_greater(),
                         suite_is_greater_or_equal(),
                         suite_is_equal(),
                         suite_is_not_equal(),

                         suite_from_int_to_decimal(),
                         suite_from_decimal_to_float(),
                         suite_from_decimal_to_int(),
                         suite_float_to_decimal(),

                         suite_truncate(),
                         suite_floor(),
                         suite_round(),
                         suite_negate(),
                         suite_round2(),
                         suite_truncate2(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
  // sleep(1);
}

int main(void) {
  run_tests();
  return 0;
}