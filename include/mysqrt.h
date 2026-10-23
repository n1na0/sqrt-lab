#ifndef MYSQRT_H_INCLUDED
#define MYSQRT_H_INCLUDED

/*
 * Приближённое вычисление квадратного корня методом итераций Ньютона.
 *
 * Вход:
 *   a   — подкоренное выражение
 *   eps — относительная погрешность (безопасная версия: eps <= 0 → NaN)
 *
 * Выход:
 *   a < 0       → NaN
 *   a == 0      → 0
 *   a == +inf   → +inf
 *   a == NaN    → NaN
 *   иначе       → приближённое значение sqrt(a)
 *
 * Реализация: "безопасная" — при eps <= 0 возвращает NaN.
 */
double my_sqrt(double a, double eps);

#endif /* MYSQRT_H_INCLUDED */