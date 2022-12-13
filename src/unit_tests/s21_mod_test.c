#include "s21_decimal_test.h"

START_TEST(mod_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_5) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal check = {{91, 0, 0, 0}};
  s21_set_scale(&check, 2);
  s21_decimal result = {0};
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mod_6) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal check = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(mod_7) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_set_sign(&value_2);
  s21_decimal check = {{91, 0, 0, 0}};
  s21_set_scale(&check, 2);
  s21_decimal result = {0};
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mod_8) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_sign(&value_1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal check = {{91, 0, 0, 0}};
  s21_set_scale(&check, 2);
  s21_set_sign(&check);
  s21_decimal result = {0};
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mod_9) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_sign(&value_1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_set_sign(&value_2);
  s21_decimal check = {{91, 0, 0, 0}};
  s21_set_scale(&check, 2);
  s21_set_sign(&check);
  s21_decimal result = {0};
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mod_10) {
  s21_decimal src1 = {0}, src2 = {0}, res_mod = {0};
  int a = -98765;
  int b = 1234;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(mod_11) {
  s21_decimal src1 = {0}, src2 = {0}, res_mod = {0};
  float a = 1.2;
  float b = 0.3;
  float res_origin = fmod(a, b);
  float res = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
}
END_TEST

Suite *suite_mod(void) {
  Suite *s = suite_create("suite_mod");
  TCase *tc = tcase_create("mod_tc");

  tcase_add_test(tc, mod_0);
  tcase_add_test(tc, mod_1);
  tcase_add_test(tc, mod_2);
  tcase_add_test(tc, mod_3);
  tcase_add_test(tc, mod_4);
  tcase_add_test(tc, mod_5);
  tcase_add_test(tc, mod_6);
  tcase_add_test(tc, mod_7);
  tcase_add_test(tc, mod_8);
  tcase_add_test(tc, mod_9);
  tcase_add_test(tc, mod_10);
  tcase_add_test(tc, mod_11);

  suite_add_tcase(s, tc);
  return s;
}