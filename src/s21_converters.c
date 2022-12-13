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

/// @brief Перевод из float в decimal
/// @param src
/// @param dst
/// @return 0 - OK 1 - ошибка конвертации
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_zero_decimal(dst);
  int scale = 0, error = 0, out = 1;
  if (src < 0) {
    s21_set_sign(dst);
    src = (-1) * src;
  }
  double src_d = (double)src;

  int exp = s21_get_exp(src_d) - 1023;
  if ((src != 0 && fabs(src) < (1e-28)) || (src > MAX_DEC)) {
    error = 1;
    s21_zero_decimal(dst);
  }
  if (!error) {
    while (scale < 28 && (long long)src_d / (long long)pow(2, 56) == 0) {
      src_d *= 10;
      scale++;
    }
    for (; fmod(src_d, 10) == 0 && scale > 0; scale--) {
      src_d /= 10;
    }
    if (scale >= 18 && scale <= 28) {
      src_d = round(src_d);
    }
    exp = s21_get_exp(src_d) - 1023;
    s21_set_scale(dst, scale);
    long long mask = 1ull << 51;
    long long unsigned int fl_to_int = *((long long unsigned *)&src_d);
    s21_set_bit(dst, exp, 1);
    for (int i = exp - 1; i >= 0 && out; i--) {
      s21_set_bit(dst, i, (fl_to_int & mask) != 0);
      mask >>= 1;
      if (!mask) out = 0;
    }
  }
  return error;
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
  temp = temp * pow(10, -s21_get_scale(&src));
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
  int scale = s21_get_scale(&src);
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

/// @brief Вычленяем экспоненту
/// @param src
/// @return
int s21_get_exp(double src) { return *((long long *)&src) >> 52; }

/// @brief  Перевод из decimal в double
/// @param src
/// @param dst
/// @return
int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  long double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_scale(&src));
  if (s21_get_bit(src, 127)) temp = temp * (-1);
  *dst = temp;
  return 0;
}