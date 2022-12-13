#ifndef _SRC_S21_DECIMAL_H_
#define _SRC_S21_DECIMAL_H_

#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define BADINT (unsigned int)0x80000000
#define START_INFO 96

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

/*------------------------ Operations with bits ------------------------- */

int s21_get_bit_big(s21_big_decimal src, int index);
void s21_set_bit_big(s21_big_decimal *dst, int index, int bit);
int s21_shift_big_dec_left(s21_big_decimal *dst, int num);
void s21_shift_big_dec_right(s21_big_decimal *dst, int num);
void s21_import_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2);
void s21_import_to_small_decimal(s21_decimal *value_1, s21_big_decimal value_2);
void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2,
                       int diff);
void s21_zero_big_decimal(s21_big_decimal *dst);

/*------------------------ Operations with bits ------------------------- */
void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
int s21_mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

/*------------------------ Ariphmetic operators ------------------------*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

/*------------------------ Arithmetic operators ------------------------*/

/*------------------------ Comparison operators ------------------------*/
void s21_comparison_reverse(int *flag);
int s21_comparison_bits(s21_decimal d1, s21_decimal d2);
int s21_greater_num(int a, int b);
int s21_comparison(s21_decimal d1, s21_decimal d2);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

/*------------------------ Comparison operators --------------------------*/

/*------------------------ Convertors and parsers ------------------------*/

int s21_get_exp(double src);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);

/*------------------------ Convertors and parsers ------------------------*/

/*------------------------ Operations with bits ------------------------- */

int s21_get_bit(s21_decimal src, int index);
int s21_get_scale(s21_decimal dst);
int s21_get_sign(s21_decimal dst);

void s21_set_bit(s21_decimal *dst, int index, int bit);
void s21_set_scale(s21_decimal *dst, int scale);
void s21_set_sign(s21_decimal *dst);
void s21_increase_scale_big_decimal(s21_big_decimal *dst, int n);
void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n);
void s21_find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                      int *bit_1, int *bit_2);
int s21_is_big_decimal_not_empty(s21_big_decimal dst);
int s21_equation_bits_big_decimal(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2);
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2);
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_get_integer_part(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);
/*------------------------ Operations with bits ------------------------- */

/*------------------------------- Decimal  ------------------------------ */

void s21_zero_decimal(s21_decimal *dst);
float s21_rand_r(float a, float b);
int s21_is_decimal_no_empty(s21_decimal dst);

/*------------------------------- Decimal  ------------------------------ */

/*------------------------  Another functions   ------------------------- */

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal dec, s21_decimal *result);
/*------------------------  Another functions   ------------------------- */

/*------------------------       Normalize      ------------------------- */
void s21_normalize(s21_decimal *d1, s21_decimal *d2);
void s21_normalize_scale_upper(s21_decimal *d, int norm);
void s21_copy_decimal(s21_decimal *d1, s21_decimal d2);
int s21_post_normalization(s21_big_decimal *result, int scale);
/*------------------------       Normalize      ------------------------- */

#endif  // _SRC_S21_DECIMAL_H_