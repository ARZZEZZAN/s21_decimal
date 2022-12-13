#include "s21_decimal.h"

/// @brief Возвращает искомый бит
/// @param dst
/// @param index
/// @return
int s21_get_bit(s21_decimal dst, int index) {
  int mask = 1u << (index % 32);
  return (dst.bits[index / 32] & mask) != 0;
}

/// @brief Получить scale
/// @param dst
/// @return
int s21_get_scale(s21_decimal dst) {
  int mask = 127 << 16;
  int scale = (mask & dst.bits[3]) >> 16;
  return scale;
}

/// @brief Получить знак
/// @param dst
/// @return
int s21_get_sign(s21_decimal dst) { return (dst.bits[3] & 1u << 31) != 0; }

/// @brief Установка бита по индексу
/// @param dst
/// @param index
/// @param bit
void s21_set_bit(s21_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}

/// @brief Установка scale
/// @param dst
/// @param scale
void s21_set_scale(s21_decimal *dst, int scale) {
  int sign = 0;
  sign = s21_get_sign(*dst);
  dst->bits[3] = 0;
  scale <<= 16;
  dst->bits[3] = scale | dst->bits[3];
  if (sign) s21_set_sign(dst);
}

/// @brief Установка знака
/// @param dst
void s21_set_sign(s21_decimal *dst) { dst->bits[3] = dst->bits[3] | 1u << 31; }
