#include "s21_decimal_test.h"

void truncate_test_function(float n, float accuracy) {
  float value0 = 0.0;
  s21_decimal var1 = {{0}}, var2 = {{0}};

  int value1 = 0, value2 = 0;
  s21_from_float_to_decimal(n, &var1);
  s21_truncate(var1, &var2);
  s21_from_decimal_to_float(var2, &value0);
  value2 = (int)value0;
  value1 = truncf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
  return;
}

START_TEST(truncate_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_4) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_5) {
  float n = s21_rand_r(-8388608, 8388608);
  truncate_test_function(n, 10);
}

START_TEST(truncate_6) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  s21_set_scale(&value_1, 3);
  s21_set_sign(&value_1);
  s21_decimal check = {{123, 0, 0, 0}};
  s21_set_sign(&check);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_8) {
  s21_decimal src1 = {0};
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res_od = {0};
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_9) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od = {0};
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

Suite *suite_truncate(void) {
  Suite *s = suite_create("suite_truncate");
  TCase *tc = tcase_create("suite_truncate_tc");

  tcase_add_test(tc, truncate_0);
  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_loop_test(tc, truncate_5, 0, 1000);
  tcase_add_test(tc, truncate_6);
  tcase_add_test(tc, truncate_7);
  tcase_add_test(tc, truncate_8);
  tcase_add_test(tc, truncate_9);

  suite_add_tcase(s, tc);
  return s;
}