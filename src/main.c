#include <stdio.h>
#include <math.h>
#include "mysqrt.h"

//вспомогательная функция для вывода результата одного теста
void check_test(double a, double eps) {
    double ans = my_sqrt(a, eps);
    
    //аргумент и ответ
    printf("a = %-10g  ans = %-12g  ", a, ans);

    //проверка ответа
    if (isnan(ans)) {
        // Если ответ NaN, проверяем, что мы его и ждали (отрицательное, NaN или eps<=0)
        if (a < 0 || isnan(a) || eps <= 0) {
            printf("-> OK \n");
        } else {
            printf("-> FAIL (получили NaN, а ждали число)\n");
        }
    } 
    else if (isinf(ans)) {
        // Если ответ бесконечность, проверяем, что и подали бесконечность
        if (isinf(a) && a > 0) {
            printf("-> OK \n");
        } else {
            printf("-> FAIL (получили бесконечность)\n");
        }
    } 
    else if (a == 0.0) {
        // Если подали ноль, ответ должен быть ноль
        if (ans == 0.0) {
            printf("-> OK (корень из 0 = 0)\n");
        } else {
            printf("-> FAIL (ждали 0)\n");
        }
    } 
    else {
        // Обычный случай: проверяем, что ans * ans примерно равно a
        //+относительная разница
        double diff = fabs(ans * ans - a);
        double max_val = fmax(fabs(ans * ans), fabs(a));
        double rel_error = diff / max_val;

        if (rel_error <= eps) {
            printf("-> OK (ans^2 = %g, разница = %g)\n", ans * ans, rel_error);
        } else {
            printf("-> FAIL (разница = %g, больше чем %g)\n", rel_error, eps);
        }
    }
}

int main() {
    double eps = 1e-12; //точность

    printf("=== ЗАПУСК ТЕСТОВ ===\n\n");

    // 1. Отрицательные
    check_test(-4.0, eps);
    check_test(-0.001, eps);

    // 2. Ноль
    check_test(0.0, eps);

    // 3. Бесконечности
    check_test(INFINITY, eps);
    check_test(-INFINITY, eps);

    // 4. Не число (NaN)
    check_test(NAN, eps);

    // 5. Маленькие числа (~1e-20)
    check_test(1e-20, eps);
    check_test(3e-20, eps);

    // 6. Средние числа (~1e-3, ~1, ~1e3)
    check_test(1e-3, eps);
    check_test(1.0, eps);
    check_test(2.5, eps);
    check_test(1e3, eps);

    // 7. Большие числа (~1e20)
    check_test(1e20, eps);
    check_test(7e20, eps);

    // 8. Некорректный eps 
    check_test(4.0, 0.0);
    check_test(4.0, -1.0);

    printf("\n=== ТЕСТЫ ЗАВЕРШЕНЫ ===\n");
    return 0;
}