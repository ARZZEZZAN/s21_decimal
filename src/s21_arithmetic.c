#include "s21_decimal.h"
/// @brief Сложение
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, get = 0, sign_res = 0;
  s21_zero_decimal(result);
  if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
    // s21_set_sign(result);
    sign_res = 1;
  }
  if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    int sign = 0;
    sign = s21_get_sign(value_1);
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
    error = sign ? s21_sub(value_2, value_1, result)
                 : s21_sub(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    int scale = 0;
    s21_import_to_big_decimal(value_1, &v1);
    s21_import_to_big_decimal(value_2, &v2);
    int diff = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (diff > 0) {
      get = s21_get_scale(value_1);
      s21_set_scale(&value_2, get);
    } else {
      get = s21_get_scale(value_2);
      s21_set_scale(&value_1, get);
    }
    s21_normalization(&v1, &v2, diff);
    s21_add_big_decimal(v1, v2, &r);
    scale = s21_post_normalization(&r, s21_get_scale(value_1));
    if (scale >= 0) {
      s21_import_to_small_decimal(result, r);
      s21_set_scale(result, scale);
    } else {
      error = 1;
    }
  }
  sign_res == 1 ? s21_set_sign(result) : 0;
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

// Сложение в формате большого децимала
void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  int res = 0, ovf = 0;
  for (int i = 0; i < 256; i++) {
    res = s21_get_bit_big(value_1, i) + s21_get_bit_big(value_2, i) + ovf;
    ovf = res / 2;
    s21_set_bit_big(result, i, res % 2);
  }
}

/// @brief Вычитание
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0, sign_res = 0;
  s21_zero_decimal(result);
  if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
    s21_decimal temporary1 = value_1;
    value_1 = value_2;
    value_2 = temporary1;
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
  }
  if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    s21_get_sign(value_1) ? sign_res = 1 : 1;
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
    error = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    s21_import_to_big_decimal(value_1, &v1);
    s21_import_to_big_decimal(value_2, &v2);
    int diff = s21_get_scale(value_1) - s21_get_scale(value_2);
    diff > 0 ? s21_set_scale(&value_2, s21_get_scale(value_2) + diff)
             : s21_set_scale(&value_1, s21_get_scale(value_1) - diff);
    s21_normalization(&v1, &v2, diff);
    if (s21_is_greater_big_decimal(v2, v1)) {
      s21_big_decimal temporary2 = v1;
      v1 = v2;
      v2 = temporary2;
      s21_set_sign(result);
    }
    s21_sub_big_decimal(v1, v2, &r);
    scale = s21_post_normalization(&r, s21_get_scale(value_1));
    if (scale >= 0) {
      s21_import_to_small_decimal(result, r);
      s21_set_scale(result, scale);
    } else {
      error = 1;
    }
  }
  sign_res == 1 ? s21_set_sign(result) : 0;

  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

// Вычитание в формате большого децимала
void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  int tmp = 0, res = 0;
  for (int i = 0; i < 256; i++) {
    res = s21_get_bit_big(value_1, i) - s21_get_bit_big(value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    s21_set_bit_big(result, i, res % 2);
  }
}

/// @brief Умножение
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0;
  s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
  s21_import_to_big_decimal(value_1, &v1);
  s21_import_to_big_decimal(value_2, &v2);
  if (s21_get_sign(value_1) != s21_get_sign(value_2)) s21_set_sign(result);
  scale = s21_get_scale(value_1) + s21_get_scale(value_2);
  error = s21_mul_big_decimal(v1, v2, &r);
  scale = s21_post_normalization(&r, scale);
  if (scale >= 0) {
    s21_set_scale(result, scale);
    s21_import_to_small_decimal(result, r);
  } else {
    error = 1;
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

/// @brief Умножение big decimal
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности
int s21_mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int error = 0, count = 0;
  for (int i = 0; i < 256 && !error; i++) {
    if (s21_get_bit_big(value_2, i)) {
      error = s21_shift_big_dec_left(&value_1, i - count);
      s21_add_big_decimal(value_1, *result, result);
      count = i;
    }
  }
  return error;
}

/// @brief Деление
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности 3 - деление на 0
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (s21_is_decimal_no_empty(value_2)) {
    int scale = 0, res_scale = 0;
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    s21_import_to_big_decimal(value_1, &v1);
    s21_import_to_big_decimal(value_2, &v2);
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) s21_set_sign(result);
    scale = s21_div_big_decimal(v1, v2, &r);
    s21_set_scale(&value_1, s21_get_scale(value_1) + scale);
    res_scale = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (res_scale > 0) {
      res_scale = s21_post_normalization(&r, res_scale);
    } else if (res_scale < 0) {
      s21_increase_scale_big_decimal(&r, abs(res_scale));
      res_scale = s21_post_normalization(&r, 0);
    }
    if (res_scale >= 0) {
      s21_import_to_small_decimal(result, r);
      s21_set_scale(result, res_scale);
    } else {
      error = 1;
    }
  } else {
    error = 3;
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

/// @brief Деление big decimal
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности 3 - деление на 0

int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int b_1 = 0, b_2 = 0, bit_2 = 0, scale = 0, diff = 0, save_scale = 0;
  s21_big_decimal tmp = {0};
  s21_find_highest_bit_big_decimal(value_1, value_2, &b_1, &b_2);
  bit_2 = b_2;
  for (int i = 0; i < 96 && s21_is_big_decimal_not_empty(value_1);) {
    if (i > 0) {
      s21_shift_big_dec_left(&value_2, 1);
      s21_increase_scale_big_decimal(result, 1);
      s21_increase_scale_big_decimal(&value_1, 1);
      save_scale++;
    }
    scale = s21_equation_bits_big_decimal(&value_1, &value_2);
    save_scale += scale;
    b_1 = b_2 = 0;
    s21_find_highest_bit_big_decimal(value_1, value_2, &b_1, &b_2);
    diff = b_2 - bit_2;
    if (diff < 0) diff = 0;
    for (; diff >= 0 && s21_is_big_decimal_not_empty(value_1);) {
      if (s21_is_greater_big_decimal(value_2, value_1)) {
        s21_set_bit_big(&tmp, 0, 0);
      } else {
        s21_sub_big_decimal(value_1, value_2, &value_1);
        s21_set_bit_big(&tmp, 0, 1);
      }
      i++;
      diff--;
      if (diff >= 0) s21_shift_big_dec_right(&value_2, 1);
      s21_shift_big_dec_left(&tmp, 1);
    }
    if (diff >= 0) s21_shift_big_dec_left(&tmp, diff + 1);
    s21_shift_big_dec_right(&tmp, 1);
    s21_add_big_decimal(*result, tmp, result);
    s21_zero_big_decimal(&tmp);
  }
  return save_scale;
}

/// @brief mod
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK
/// 1 - число слишком велико или равно бесконечности
/// 2 - число слишком мало или равно отрицательной бесконечности
/// 3 - деление на 0
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, sign = 0;
  if (s21_get_sign(value_1)) sign = 1;
  s21_set_bit(&value_1, 127, 0);
  s21_set_bit(&value_2, 127, 0);
  if (!s21_is_decimal_no_empty(value_2)) {
    error = 3;
  } else {
    if (s21_is_greater_or_equal(value_1, value_2)) {
      s21_decimal tmp = {0};
      error = s21_get_integer_part(value_1, value_2, &tmp);
      if (!error) {
        s21_decimal tmp1 = {0};
        error = s21_mul(value_2, tmp, &tmp1);
        if (!error) {
          error = s21_sub(value_1, tmp1, result);
        }
      }
    } else {
      *result = value_1;
    }
  }
  s21_set_bit(result, 127, sign);
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

/// @brief Берет целую часть
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK
/// 1 - число слишком велико или равно бесконечности
/// 2 - число слишком мало или равно отрицательной бесконечности
int s21_get_integer_part(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  int high_bit = 0, b1 = 0, b2 = 0, error = 0;
  s21_big_decimal tmp_rem = {0}, v1 = {0}, v2 = {0}, nvalue = {0},
                  one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_import_to_big_decimal(value_1, &v1);
  s21_import_to_big_decimal(value_2, &v2);
  while (s21_is_greater_big_decimal(v2, v1)) {
    s21_increase_scale_big_decimal(&v1, 1);
    s21_set_scale(&value_1, s21_get_scale(value_1) + 1);
  }
  int scale = s21_get_scale(value_2) - s21_get_scale(value_1);
  s21_find_highest_bit_big_decimal(v1, v2, &b1, &b2);
  for (int j = b1; j >= 0; j--) {
    s21_set_bit_big(&nvalue, j, !s21_get_bit_big(v2, j));
  }
  s21_add_big_decimal(nvalue, one, &nvalue);
  for (int j = b1; j >= 0; j--) {
    s21_shift_big_dec_left(&tmp_rem, 1);
    high_bit = s21_get_bit_big(tmp_rem, b1);
    s21_set_bit_big(&tmp_rem, b1 + 1, 0);
    s21_set_bit_big(&tmp_rem, 0, s21_get_bit_big(v1, b1));
    s21_shift_big_dec_left(&v1, 1);
    s21_set_bit_big(&v1, b1 + 1, 0);
    if (high_bit) {
      s21_add_big_decimal(tmp_rem, v2, &tmp_rem);
    } else {
      s21_add_big_decimal(tmp_rem, nvalue, &tmp_rem);
    }
    s21_set_bit_big(&tmp_rem, b1 + 1, 0);
    high_bit = s21_get_bit_big(tmp_rem, b1);
    s21_set_bit_big(&v1, 0, !high_bit);
  }
  if (scale < 0) {
    s21_increase_scale_big_decimal(&v1, -scale);
    scale = s21_post_normalization(&v1, 0);
  } else {
    scale = s21_post_normalization(&v1, scale);
  }
  if (scale >= 0) {
    s21_set_scale(result, scale);
    s21_import_to_small_decimal(result, v1);
  } else {
    error = 1;
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

/// @brief Перенос данных из decimal в big decimal
/// @param value_1
/// @param value_2
void s21_import_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
}

/// @brief Перенос данных из big decimal в decimal
/// @param value_1
/// @param value_2
void s21_import_to_small_decimal(s21_decimal *value_1,
                                 s21_big_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
}

/// @brief Установить бит в большой структуре
/// @param dst
/// @param index
/// @param bit
void s21_set_bit_big(s21_big_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}

/// @brief Получение бита в большой структуре
/// @param dst
/// @param index
/// @return
int s21_get_bit_big(s21_big_decimal dst, int index) {
  int mask = 1u << (index % 32);
  return (dst.bits[index / 32] & mask) != 0;
}

/// @brief Сдвиг big decimal вправо +
/// @param dst
/// @param num
void s21_shift_big_dec_right(s21_big_decimal *dst, int num) {
  int buffer[7] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = s21_get_bit_big(*dst, (i + 1) * 32);
    }
    for (int i = 0; i < 7; i++) {
      dst->bits[i] >>= 1;
      s21_set_bit_big(dst, (i + 1) * 32 - 1, buffer[i]);
    }
    dst->bits[7] >>= 1;
  }
}

/// @brief Сдвиг big decimal влево +
/// @param dst
/// @param num
/// @return
int s21_shift_big_dec_left(s21_big_decimal *dst, int num) {
  int error = 0;
  int buffer[8] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = s21_get_bit_big(*dst, (i + 1) * 32 - 1);
    }
    for (int i = 7; i > 0 && !error; i--) {
      if (s21_get_bit_big(*dst, 255)) error = 1;
      dst->bits[i] <<= 1;
      s21_set_bit_big(dst, i * 32, buffer[i - 1]);
    }
    dst->bits[0] <<= 1;
  }
  return error;
}

/// @brief Нормализация для big decimal
/// @param value_1
/// @param value_2
/// @param diff
void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2,
                       int diff) {
  if (diff > 0) {
    s21_increase_scale_big_decimal(value_2, diff);
  } else if (diff < 0) {
    s21_increase_scale_big_decimal(value_1, -diff);
  }
}

/// @brief Пост нормализация для big decimal
/// @param result
/// @param scale
/// @return Число больше, равно или меньше нуля
int s21_post_normalization(s21_big_decimal *result, int scale) {
  int dop = 0;
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (scale == 1 && result->bits[3]) dop = 1;
    s21_decreace_scale_big_decimal(result, 1);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 && s21_get_bit_big(*result, 0))
    s21_set_bit_big(result, 0, 0);
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7]))
    scale = -1;
  return scale;
}

/// @brief Обнуление big decimal
/// @param dst
void s21_zero_big_decimal(s21_big_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = dst->bits[4] =
      dst->bits[5] = dst->bits[6] = dst->bits[7] = 0;
}

/// @brief Увеличение scale decimal на n
/// @param dst
/// @param n
void s21_increase_scale_decimal(s21_decimal *dst, int n) {
  s21_decimal tmp = {0}, ten = {{10, 0, 0, 0}};
  int scale = s21_get_scale(*dst);
  for (int i = 0; i < n; i++) {
    s21_mul(*dst, ten, &tmp);
    *dst = tmp;
    s21_zero_decimal(&tmp);
  }
  s21_set_scale(dst, scale + n);
}

/// @brief Увеличение scale big decimal на n
/// @param dst
/// @param n
void s21_increase_scale_big_decimal(s21_big_decimal *dst, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    s21_mul_big_decimal(*dst, ten, &tmp);
    *dst = tmp;
    s21_zero_big_decimal(&tmp);
  }
}

/// @brief Уменьшение scale big decimal на n
/// @param dst
/// @param n
void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    s21_div_big_decimal(*dst, ten, &tmp);
    *dst = tmp;
    s21_zero_big_decimal(&tmp);
  }
}

/// @brief Больше
/// @param value_1
/// @param value_2
/// @return 0 - если < , 1 - если >
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

/// @brief Больше или равно
/// @param value_1
/// @param value_2
/// @return 0 - если < , 1 - если >=
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !out && !result; i--) {
    if (value_1.bits[i] != 0 || value_2.bits[i] != 0) {
      if (value_1.bits[i] >= value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

/// @brief Проверка на пустоту
/// @param dst
/// @return 0 или число большее 0
int s21_is_decimal_no_empty(s21_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2];
}

/// @brief Проверка на пустоту
/// @param dst
/// @return 0 или число большее 0
int s21_is_big_decimal_not_empty(s21_big_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2] + dst.bits[3] + dst.bits[4] +
         dst.bits[5] + dst.bits[6] + dst.bits[7];
}

/// @brief Поиск наибольшего бита
/// @param v1
/// @param v2
/// @param bit_1
/// @param bit_2
void s21_find_highest_bit_decimal(s21_decimal v1, s21_decimal v2, int *bit_1,
                                  int *bit_2) {
  for (int i = 95; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && s21_get_bit(v1, i)) *bit_1 = i;
    if (*bit_2 == 0 && s21_get_bit(v2, i)) *bit_2 = i;
  }
}

/// @brief  Поиск наибольшего бита в big decimal
/// @param v1
/// @param v2
/// @param bit_1
/// @param bit_2
void s21_find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                      int *bit_1, int *bit_2) {
  for (int i = 255; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && s21_get_bit_big(v1, i)) *bit_1 = i;
    if (*bit_2 == 0 && s21_get_bit_big(v2, i)) *bit_2 = i;
  }
}

/// @brief Уравнение big decimal
/// @param value_1
/// @param value_2
/// @return scale
int s21_equation_bits_big_decimal(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2) {
  int scale = 0;
  while (s21_is_greater_big_decimal(*value_2, *value_1)) {
    s21_increase_scale_big_decimal(value_1, 1);
    scale++;
  }
  while (s21_is_greater_or_equal_big_decimal(*value_1, *value_2)) {
    s21_shift_big_dec_left(value_2, 1);
  }
  s21_shift_big_dec_right(value_2, 1);
  return scale;
}
