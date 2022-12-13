#include "s21_decimal_test.h"

START_TEST(s21_get_bit_0) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int res = 1;
  ck_assert_int_eq(res, s21_get_bit(val1, 0));
}
END_TEST

START_TEST(s21_get_bit_1) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int res = 0;
  ck_assert_int_eq(res, s21_get_bit(val1, 5));
}
END_TEST

START_TEST(s21_get_bit_2) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000001111110000, 0b00000000000000000000000000000000}};
  int res = 1;
  ck_assert_int_eq(res, s21_get_bit(val1, 70));
}
END_TEST

START_TEST(s21_get_bit_3) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000001111110000, 0b00000000000000000000000000000000}};
  int res = 0;
  ck_assert_int_eq(res, s21_get_bit(val1, 64));
}
END_TEST

START_TEST(s21_get_bit_4) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b11111111111111100000000000000000,
       0b00000000100011001010000000000000, 0b10000000000000000111111110000000}};
  int res = 1;
  ck_assert_int_eq(res, s21_get_bit(val1, 127));
}
END_TEST

START_TEST(s21_get_bit_5) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b11111111111111100000000000000000,
       0b00000000100011001010000000000000, 0b00000000000000000111111110000000}};
  int res = 0;
  ck_assert_int_eq(res, s21_get_bit(val1, 127));
}
END_TEST

START_TEST(s21_get_scale_0) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000010000000000000000}};
  int res = 1;
  ck_assert_int_eq(res, s21_get_scale(&val1));
}
END_TEST

START_TEST(s21_get_scale_1) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  int res = 5;
  ck_assert_int_eq(res, s21_get_scale(&val1));
}
END_TEST

START_TEST(s21_get_scale_2) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000100000000000000000000}};
  int res = 16;
  ck_assert_int_eq(res, s21_get_scale(&val1));
}
END_TEST

START_TEST(s21_get_scale_3) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000111000000000000000000}};
  int res = 28;
  ck_assert_int_eq(res, s21_get_scale(&val1));
}
END_TEST

START_TEST(s21_get_scale_4) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000001111000000000000000000}};
  int res = 60;
  ck_assert_int_eq(res, s21_get_scale(&val1));
}
END_TEST

START_TEST(s21_get_scale_5) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000111100000000000000000}};
  int res = 30;
  ck_assert_int_eq(res, s21_get_scale(&val1));
}
END_TEST

START_TEST(s21_get_sign_0) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  int res = 1;
  ck_assert_int_eq(res, s21_get_sign(&val1));
}
END_TEST

START_TEST(s21_get_sign_1) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  int res = 0;
  ck_assert_int_eq(res, s21_get_sign(&val1));
}
END_TEST

START_TEST(s21_get_sign_2) {
  s21_decimal val1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b01111111111111111111111111111111}};
  int res = 0;
  ck_assert_int_eq(res, s21_get_sign(&val1));
}
END_TEST

START_TEST(s21_set_bit_0) {
  s21_decimal val1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b01111111111111111111111111111111}};
  s21_decimal val2 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b01111111111111111111111111111111}};

  s21_set_bit(&val1, 0, 0);
  int orig = s21_is_equal(val1, val2);
  int res = 0;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_bit_1) {
  s21_decimal val1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b01111111111111111111111111111111}};
  s21_decimal val2 = {
      {0b11111111111111111111111111111110, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b11111111111111111111111111111111}};

  s21_set_bit(&val1, 0, 0);
  s21_set_bit(&val1, 127, 1);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_bit_2) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b10000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000001, 0b01000010000000000000000000000000}};

  s21_set_bit(&val1, 0, 0);
  s21_set_bit(&val1, 31, 1);
  s21_set_bit(&val1, 64, 1);
  s21_set_bit(&val1, 120, 1);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_scale_0) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};

  s21_set_scale(&val1, 5);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_scale_1) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000100000000000000000000}};

  s21_set_scale(&val1, 16);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_scale_2) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000111000000000000000000}};

  s21_set_scale(&val1, 28);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_scale_3) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000001111000000000000000000}};

  s21_set_scale(&val1, 60);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_scale_4) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000111100000000000000000}};

  s21_set_scale(&val1, 30);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_set_sign_0) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_set_sign(&val1);
  int orig = s21_is_equal(val1, val2);
  int res = 1;
  ck_assert_int_eq(res, orig);
}
END_TEST

Suite *suite_get_set(void) {
  Suite *s = suite_create("suite_get_set");
  TCase *tc = tcase_create("case_get_set");

  tcase_add_test(tc, s21_get_bit_0);
  tcase_add_test(tc, s21_get_bit_1);
  tcase_add_test(tc, s21_get_bit_2);
  tcase_add_test(tc, s21_get_bit_3);
  tcase_add_test(tc, s21_get_bit_4);
  tcase_add_test(tc, s21_get_bit_5);

  tcase_add_test(tc, s21_get_scale_0);
  tcase_add_test(tc, s21_get_scale_1);
  tcase_add_test(tc, s21_get_scale_2);
  tcase_add_test(tc, s21_get_scale_3);
  tcase_add_test(tc, s21_get_scale_4);
  tcase_add_test(tc, s21_get_scale_5);

  tcase_add_test(tc, s21_get_sign_0);
  tcase_add_test(tc, s21_get_sign_1);
  tcase_add_test(tc, s21_get_sign_2);

  tcase_add_test(tc, s21_set_bit_0);
  tcase_add_test(tc, s21_set_bit_1);
  tcase_add_test(tc, s21_set_bit_2);

  tcase_add_test(tc, s21_set_scale_0);
  tcase_add_test(tc, s21_set_scale_1);
  tcase_add_test(tc, s21_set_scale_2);
  tcase_add_test(tc, s21_set_scale_3);
  tcase_add_test(tc, s21_set_scale_4);

  tcase_add_test(tc, s21_set_sign_0);

  suite_add_tcase(s, tc);
  return s;
}
