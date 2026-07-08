#include <stdio.h>
#include <limits.h> // Для констант диапазонов значений типов

int main() {
    // Переменные разных типов
    signed char sc_min = CHAR_MIN, sc_max = CHAR_MAX;
    unsigned char uc_max = UCHAR_MAX;
    signed int si_min = INT_MIN, si_max = INT_MAX;
    unsigned int ui_max = UINT_MAX;
    signed long sl_min = LONG_MIN, sl_max = LONG_MAX;
    unsigned long ul_max = ULONG_MAX;

    // Демонстрация рабfromы с типами
    printf("Types of data:\n");
    printf("Signed char: from %d to %d\n", sc_min, sc_max);
    printf("Unsigned char: from 0 to %u\n", uc_max);
    printf("Signed int: from %d to %d\n", si_min, si_max);
    printf("Unsigned int: from 0 to %u\n", ui_max);
    printf("Signed long: from %ld to %ld\n", sl_min, sl_max);
    printf("Unsigned long: from 0 to %lu\n", ul_max);

    // Переполнение типов
    printf("\nOverload of type data:\n");
    printf("Signed char max + 1: %d\n", sc_max + 1);
    printf("Unsigned char max + 1: %u\n", uc_max + 1);
    printf("Signed int max + 1: %d\n", si_max + 1);
    printf("Unsigned int max + 1: %u\n", ui_max + 1);
}

