#include <iostream>
using namespace std;

const int SIZE=100; // Размер строки

int main() { 
  char str[SIZE]; // Строка для обработки
  int len=0; // Длинна строки 

  cout << "Введите строку: "; 
  cin.getline(str, SIZE); // Получение строки из cli

  // Алгоритм перебора
  for(int i=0; str[i] != '\0'; i++) { // Цикл для "первого символа"
    for(int j=i+1; str[j] != '\0'; j++) { // Цикл для "второго символа"
      
      // Получение длинны строки
      while(str[len] != '\0'){
        len++;
      }

      // Поиск совпадения символов
      if(str[i] == str[j]) {
        for(int k=j; k < len - 1; k++) { // Сдвиг символов влево на один
          str[k] = str[k+1];
        }

        // Укорачеваем строку
        str[len - 1] = '\0';
      }
    }
  }

  cout << "Полученая строка: "; 

  // Вывод строки
  for(int i=0; str[i] != '\0'; i++) {
    cout << str[i];
  }

  cout << endl;

}
