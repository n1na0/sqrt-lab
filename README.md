# Лабораторная работа 8.5: Приближенное вычисление квадратного корня

Реализация функции `my_sqrt(a, eps)` методом итераций Ньютона. Проект разделен на модули:

- `include/mysqrt.h` — интерфейс функции
- `src/mysqrt.c` — реализация
- `src/main.c` — интерфейс и автоматические тесты
## Сборка и запуск
gcc -std=c99 -Wall -Wextra -Iinclude src/mysqrt.c src/main.c -o sqrt_test -lm
./sqrt_test
