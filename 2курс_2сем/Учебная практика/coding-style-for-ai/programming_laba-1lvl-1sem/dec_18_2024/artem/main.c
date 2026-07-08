#include <stdio.h>
#include <math.h>
#include <string.h> 
#include <time.h>

int main() {
  char name[] = "Fedorov"; // Фамилия автора
  clock_t t1_start; // Начальное время процессора
  clock_t t1_end;   // Конечное время процессора
  time_t t2_start;  // Начальное реальное время
  time_t t2_end;    // Конечное реальное время
  double t1_time;   // Затраченное время процессора
  double t2_time;   // Затраченное реальное время
  int stepen2 = pow(2, 32); // 2 в степени 32
  unsigned long long ten = 1; // Степень двойки в десятичной системе
  unsigned long long sixteen = 1; // Степень двойки в 16-ричной системе
  unsigned long long two = 1; // Текущее значение степени двойки
  unsigned long long two_old = 1; // Предыдущее значение степени двойки
  int i = 0; // Счётчик для вывода
  int lenth_author_second_name = strlen(name); // Длина фамилии
  int sdvig_left; // Результат сдвига влево
  int sdvig_right; // Результат сдвига вправо

  t1_start = clock(); // Запуск таймера процессора
  time(&t2_start);    // Запуск реального времени

  // Цикл для вывода степеней двойки
  while (i != 64) {
    ten = pow(2, i); // В десятичной системе
    sixteen = pow(2, i); // В 16-ричной системе
    
    // Вывод значений
    printf("%-28llu %-16llx \n", ten, sixteen); 
    i += 1;
  }  

  printf("\n");

  // Цикл для вывода фамилии автора при разнице в 1 триллион
  for (int i = 48; i != -1 ; i += 10) {
    two = pow(2, i); // Расчёт степени двойки

    if (two == 0) { // Остановка при переполнении
      break;
    }

    if ((two - two_old) >= 1000000000000) { // Если разница больше 1 триллион
      printf("%-19llu", two);
      printf("%-15s\n", name); // Вывод фамилии
      two_old = two; // Обновление старого значения
    } else {
      printf("%llu\n", two); // Вывод значения
    }
  }

  printf("\n");

  // Сдвиги для первой переменной
  printf("%s\n", "Sdvig 1");
  sdvig_left = stepen2 << lenth_author_second_name; // Сдвиг влево
  printf("\t%s %d\n", "left:", sdvig_left); 
  sdvig_right = sdvig_left >> lenth_author_second_name; // Сдвиг вправо
  printf("\t%s %d\n", "right:", sdvig_right); 

  // Сдвиги для второй переменной
  printf("\n%s\n", "Sdvig 2");
  sdvig_right = stepen2 >> lenth_author_second_name; // Сдвиг вправо
  printf("\t%s %d\n", "right:", sdvig_right); 
  sdvig_left = sdvig_right << lenth_author_second_name; // Сдвиг влево
  printf("\t%s %d\n", "left:", sdvig_left); 

  t1_end = clock(); // Конец таймера процессора
  time(&t2_end);    // Конец реального времени

  t1_time = ((double)(t1_end - t1_start)) / CLOCKS_PER_SEC; // Время процессора
  t2_time = difftime(t2_end, t2_start); // Реальное время

  // Вывод времени
  printf("\nTIME:\n\tCPU time: %0.4f sec.\n\tReal time: %0.4f sec.\n", t1_time, t2_time);
}
