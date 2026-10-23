#include <stdio.h>
#include <math.h>
#include <float.h>
#include "mysqrt.h"

/* ---------- Вспомогательные функции ---------- */

/* Относительная разница двух чисел (защита от деления на ноль) */
static double rel_diff(double x, double y)
{
    double d = fabs(x - y);
    double m = fmax(fabs(x), fabs(y));
    return (m > 0.0) ? (d / m) : d;
}

/*
 * Один тест-кейс.
 *   name   — название теста
 *   a, eps — вход
 *   expect — 'n' (NaN), 'i' (+inf), '0' (ноль), 'v' (валидное число)
 * Возвращает 1 если тест пройден, 0 иначе.
 */
static int run_case(const char *name, double a, double eps, char expect)
{
    double ans = my_sqrt(a, eps);
    int ok = 0;
    const char *verdict = "";

    switch (expect) {
    case 'n':
        ok = isnan(ans);
        verdict = ok ? "OK (NaN)" : "FAIL (ожидался NaN)";
        break;
    case 'i':
        ok = isinf(ans) && ans > 0;
        verdict = ok ? "OK (+inf)" : "FAIL (ожидался +inf)";
        break;
    case '0':
        ok = (ans == 0.0);
        verdict = ok ? "OK (0)" : "FAIL (ожидался 0)";
        break;
    case 'v': {
        /* Проверяем, что ans^2 ≈ a с относительной погрешностью */
        double check = rel_diff(ans * ans, a);
        double tol = eps + 4.0 * DBL_EPSILON;
        ok = (check <= tol) && (ans >= 0.0);
        if (ok) {
            verdict = "OK (ans^2 ≈ a)";
        } else {
            printf("  [%s] a=%-12g eps=%-8g ans=%-15g FAIL (rel_diff=%.3e > %.3e)\n",
                   name, a, eps, ans, check, tol);
            return 0;
        }
        break;
    }
    default:
        verdict = "?";
        break;
    }

    printf("  [%s] a=%-12g eps=%-8g ans=%-15g %s\n",
           name, a, eps, ans, verdict);
    return ok;
}

/* ---------- Все тесты ---------- */

static int run_all_tests(void)
{
    const double eps = 1e-12;
    int passed = 0, total = 0;

    printf("=== Автоматические тесты my_sqrt ===\n");

    /* 1. Отрицательное */
    ++total; passed += run_case("negative",  -4.0, eps, 'n');

    /* 2. Нулевое */
    ++total; passed += run_case("zero",       0.0, eps, '0');

    /* 3. +inf и -inf */
    ++total; passed += run_case("+inf",   INFINITY, eps, 'i');
    ++total; passed += run_case("-inf",  -INFINITY, eps, 'n');

    /* 4. NaN */
    ++total; passed += run_case("NaN",        NAN, eps, 'n');

    /* 5. Малый порядок ~1e-20 */
    ++total; passed += run_case("tiny 1e-20", 1e-20, eps, 'v');
    ++total; passed += run_case("tiny 3e-20", 3e-20, eps, 'v');

    /* 6. Средний порядок ~1e-3, ~1, ~1e3 */
    ++total; passed += run_case("mid 1e-3",   1e-3,  eps, 'v');
    ++total; passed += run_case("mid 1",      1.0,   eps, 'v');
    ++total; passed += run_case("mid 2",      2.0,   eps, 'v');
    ++total; passed += run_case("mid 1e3",    1e3,   eps, 'v');

    /* 7. Большой порядок ~1e20 */
    ++total; passed += run_case("big 1e20",   1e20,  eps, 'v');
    ++total; passed += run_case("big 7e20",   7e20,  eps, 'v');

    /* 8. Некорректный eps (безопасная версия) */
    ++total; passed += run_case("eps=0",      4.0,   0.0,  'n');
    ++total; passed += run_case("eps<0",      4.0,  -1.0,  'n');

    printf("--------------------------------------\n");
    printf("Итого: %d/%d тестов пройдено\n", passed, total);
    return (passed == total) ? 0 : 1;
}

/* ---------- main ---------- */

int main(void)
{
    int rc = run_all_tests();

    /* Ручной ввод (опционально) */
    double a, e;
    printf("\nВведите a и eps через пробел (Ctrl+D / Ctrl+Z — выход): ");
    if (scanf("%lf %lf", &a, &e) == 2) {
        double r = my_sqrt(a, e);
        printf("my_sqrt(%g, %g) = %g\n", a, e, r);
        if (!isnan(r) && !isinf(r) && r >= 0.0) {
            printf("проверка: rel_diff(ans^2, a) = %.3e\n",
                   rel_diff(r * r, a));
        }
    }

    return rc;
}