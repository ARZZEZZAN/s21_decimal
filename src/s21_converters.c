#include "s21_decimal.h"

/// @brief  Перевод из int в decimal
/// @param src
/// @param dst
/// @return 0 - OK 1 - ошибка конвертации
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_zero_decimal(dst);
  int error = 0;
  if (src < 0) {
    s21_set_sign(dst);
    src = (-1) * src;
  }
  if (src > INT_MAX)
    error = 1;
  else
    dst->bits[0] = src;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_zero_decimal(dst);
  int return_value = 0;
  if (isinf(src) || isnan(src)) {
    return_value = 1;
  } else {
    if (src != 0) {
      int sign = *(int *)&src >> 31;
      int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      double temp = (double)fabs(src);
      int off = 0;
      for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
      }
      temp = round(temp);
      if (off <= 28 && (exp > -94 && exp < 96)) {
        floatbits mant = {0};
        temp = (float)temp;
        for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
        }
        mant.fl = temp;
        exp = ((*(int *)&mant.fl & ~0x80000000) >> 23) - 127;
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--)
          if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
        dst->bits[3] = (sign << 31) | (off << 16);
      }
    }
  }
  return return_value;
}

/// @brief Перевод из decimal во float
/// @param src
/// @param dst
/// @return 0 - OK 1 - ошибка конвертации
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_scale(src));
  if (s21_get_bit(src, 127)) temp = temp * (-1);
  *dst = temp;
  return 0;
}

/// @brief  Перевод из decimal в int
/// @param src
/// @param dst
/// @return
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int scale = s21_get_scale(src);
  if (src.bits[1] || src.bits[2]) {
    error = 1;
  } else {
    *dst = src.bits[0];
    if (scale > 0 && scale <= 28) {
      *dst /= pow(10, scale);
    }
  }
  if (s21_get_bit(src, 127)) *dst = *dst * (-1);
  return error;
}

/// @brief  Перевод из decimal в double
/// @param src
/// @param dst
/// @return
int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  long double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_scale(src));
  if (s21_get_bit(src, 127)) temp = temp * (-1);
  *dst = temp;
  return 0;
}