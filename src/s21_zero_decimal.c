#include "s21_decimal.h"

/// @brief Обнуление decimal
/// @param dst
void s21_zero_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}