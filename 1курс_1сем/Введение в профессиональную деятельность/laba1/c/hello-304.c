#include <stdio.h>
#include <time.h>

int main() {
    printf("Hello 304 from Egorov Alexander a.k.a. swrneko\n☆*:.｡.o(≧▽≦)o.｡.:*☆\n"); 

    // Получаем текущее время
    time_t now;
    time(&now);

    // Преобразуем его в локальное время
    struct tm* local = localtime(&now);

    // Выводим дату и время
    printf("Текущая дата и время: %02d-%02d-%04d %02d:%02d:%02d\n",
        local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
        local->tm_hour, local->tm_min, local->tm_sec);

    return 0;
}
