#include <math.h>
#include "mysqrt.h"

double my_sqrt(double a, double eps)
{
    /* --- Безопасная версия: проверка корректности eps --- */
    if (isnan(eps) || eps <= 0.0) return NAN;

    /* --- Обработка особых случаев аргумента --- */
    if (isnan(a)) return a;      /* NaN → NaN */
    if (a < 0.0)  return NAN;    /* отрицательное → NaN */
    if (a == 0.0) return 0.0;    /* ноль → ноль */
    if (isinf(a)) return a;      /* +inf → +inf (для -inf отсечено выше) */

    /* --- Основной итерационный процесс --- */
    double x_prev = a;                               /* x_0 = a */
    double x_cur  = 0.5 * (x_prev + a / x_prev);     /* x_1 */

    while (fabs((x_cur - x_prev) / x_cur) >= eps) {
        x_prev = x_cur;
        x_cur  = 0.5 * (x_prev + a / x_prev);
    }
    return x_cur;
}