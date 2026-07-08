/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                 *
* Project Name  : proj_2                                        *
* File Name     : main.cpp                                      *
* Language      : C/C++                                         *
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И.            *
* Modifyed By   : Егоров А.В (swrneko)                          *
* Edited by     : Neovim, Visual Studio                         *
* OS            : Arch Linux, Windows 11                        *
* Github url    : https://github.com/swrneko/mai_shit.git       *
* Created       : 13/11/24                                      *
* Last Revision : 24/11/24                                      *
* Comment(s)    : Табулирование функций.                        *
****************************************************************/

/****************************************
* Подключение препроцессора и библиотек *
****************************************/
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

/*********
* Алиасы *
*********/
#define step_lenth ((b - a) / n) // Формула величины шага
#define arg_increment (a + (i * h)) // Формула приращения аргумента
#define F(Xi) (2 - cos(xi)) // F(xi)
#define G(Xi) (1 - pow(xi,2)) // G(xi)

/*************
* Переменные *
*************/
float a; // Начальная точка отрезка
float b; // Конечная точка отрезка
float h; // Величина шага
float x; // Аргумент функций
float xi; // Приращение аргумента
int n; // Количество интервалов
int i = 0;

/****************
* Основное тело *
****************/
int main() {
  // Ввод начальной информации
  cout << "Введите точку А: ";
  cin >> a;
  cout << "Введите точку B: ";
  cin >> b;
  cout << "Введите количество интервалов N: ";
  cin >> n;

  // Начальные вычисления
  h = step_lenth; // Вычисление шага

//  cout << "| N | " << "Xi | " << "F(xi) | " << "G(xi) |" << endl;
  cout << "N " 
       << setw(9) << "Xi "
       << setw(12) << "F(Xi) "
       << setw(12) << "G(Xi) "
       << endl;

  // Основные вычисления
  while (i != n) {
    i += 1;
    xi = arg_increment; // Начальное вычисление приращения аргумента
    cout.width(8);
    cout << left << i << setw(9)
         << left << xi << setw(12)
         << left << F(xi) << setw(2)
         << left << G(xi) << setw(2)
         << endl;
  }
}
