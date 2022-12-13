#include "s21_decimal_test.h"

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_scale(&value_2, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  s21_set_sign(&value_2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  s21_set_sign(&check);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_set_sign(&value_1);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  s21_set_sign(&value_2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{125, 0, 0, 0}};
  s21_set_scale(&check, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_set_sign(&value_1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *suite_div(void) {
  Suite *s = suite_create("suite_div");
  TCase *tc = tcase_create("case_div");

  tcase_add_test(tc, div_0);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);

  suite_add_tcase(s, tc);
  return s;
}
