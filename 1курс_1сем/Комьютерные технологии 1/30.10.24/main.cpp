/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                 *
* Project Name  : proj_1                                        *
* File Name     : main.cpp                                      *
* Language      : C/C++                                         *
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И.            *
* Modifyed By   : Егоров А.В (swrneko)                          *
* Edited by     : Neovim, Visual Studio                         *
* OS            : Arch Linux, Windows 11                        *
* Github url    : https://github.com/swrneko/mai_shit.git       *
* Lit source    :                                               *
* Created       : 05/11/24                                      *
* Last Revision : 27/11/24                                      *
* Comment(s)    : Сумма ряда.                                   *
****************************************************************/
#include <cmath>
#include <iostream>
using namespace std;

int main() { // основная функция
  float tsum;  // точная сумма
  int n; // порядковый номер элемента
  float sum; // сумма
  float eps; // ввод точности
  float diff; // разность точного значенме и суммы

  setlocale(LC_ALL, "Russian");

  cout << "Введите точность: ";
  cin >> eps;

  if (eps <= 0) {
    cout << "Введённое число меньше или равно нулю.\n";
    exit(1);
  }

  tsum = 0.75;
  n = 2;
  sum = 0;
  diff = abs(tsum - sum);

  while (diff >= eps) {
    sum = (sum + (1.0 / ((n - 1)*(n + 1))));
    n += 1;
    diff = abs(tsum - sum);
  }
  cout << "Количество просуммированных элементов: " << (n - 2) << "\nСумма: " << sum << "\nРазность суммы и точного значения: " << diff << endl;
}

