#include "s21_decimal.h"
/// @brief изменение флага на противоложный
/// @param flag
void s21_comparison_reverse(int *flag) {
  if (*flag == 1) {
    *flag = 2;
  } else if (*flag == 2) {
    *flag = 1;
  }
}

/// @brief побитовое сравнение двух decimal
/// @param d1
/// @param d2
/// @return
int s21_comparison_bits(s21_decimal d1, s21_decimal d2) {
  int bit1 = 0;
  int bit2 = 0;
  int flag = 0;
  for (int i = 95; i >= 0 && !flag; --i) {
    bit1 = s21_get_bit(d1, i);
    bit2 = s21_get_bit(d2, i);
    if (bit1 > bit2) {
      flag = 1;
    } else if (bit1 < bit2) {
      flag = 2;
    }
  }
  return flag;
}

/// @brief поиск наибольшего числа
/// @param a
/// @param b
/// @return возвращает 0, 1, 2, если a = b, a > b, a < b соответсвенно
int s21_greater_num(int a, int b) {
  int flag = 0;
  if (a > b) {
    flag = 1;
  } else if (a < b) {
    flag = 2;
  } else if (a == b) {
    flag = 0;
  }
  return flag;
}

/// @brief Преобразоветли
/// @param d1
/// @param d2
/// @return 0, 1, 2, если d1 = d2, d1 > d2, d1 < d2 соответсвенно
int s21_comparison(s21_decimal d1, s21_decimal d2) {
  int flag = 0;
  int scale_dif = (s21_get_scale(d1) - s21_get_scale(d2));
  s21_normalize(&d1, &d2);
  flag = s21_greater_num(!s21_get_sign(d1), !s21_get_sign(d2));
  if (flag == 0) {
    if (scale_dif >= 0) {
      flag = s21_comparison_bits(d1, d2);
    } else {
      scale_dif = -scale_dif;
      flag = s21_comparison_bits(d2, d1);
      s21_comparison_reverse(&flag);
    }
    if (s21_get_sign(d1) && s21_get_sign(d2)) {
      s21_comparison_reverse(&flag);
    }
  } else {
    if (d1.bits[0] == 0 && d1.bits[1] == 0 && d1.bits[2] == 0 &&
        d2.bits[0] == 0 && d2.bits[1] == 0 && d2.bits[2] == 0) {
      flag = 0;
    }
  }
  return flag;
}

/// @brief Функция Меньше <
/// @param d1
/// @param d2
/// @return
int s21_is_less(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 2) ? 1 : 0;
}

/// @brief Функция Меньше или равно <=
/// @param d1
/// @param d2
/// @return
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 2) || (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

/// @brief Функция Больше >
/// @param d1
/// @param d2
/// @return
int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 1) ? 1 : 0;
}

/// @brief Функция Больше или равно >=
/// @param d1
/// @param d2
/// @return
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 1) || (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

/// @brief Функция Равно ==
/// @param d1
/// @param d2
/// @return
int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

/// @brief Не равно !=
/// @param d1
/// @param d2
/// @return
int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 0) ? 0 : 1;
}
