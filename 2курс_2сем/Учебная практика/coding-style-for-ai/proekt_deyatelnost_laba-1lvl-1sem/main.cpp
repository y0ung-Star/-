/*************************************************************************************
*                              КАФЕДРА № 304 1 КУРС                                  *
*------------------------------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                                      *
* Project Name  : laba_0                                                             *
* File Name     : main.cpp                                                           *
* Language      : C/C++                                                              *
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И, Трифанов А.Л, Мурзамуратов И.Н. *
* Modifyed By   : Егоров А.В (swrneko)                                               *
* Edited by     : Neovim, Visual Studio, Sublime Text                                *
* OS            : Arch Linux, Windows 11/10                                          *
* Github url    : https://github.com/swrneko/mai_shit.git                            *
* Created       : 24.12/24                                                           *
* Last Revision : 24/12/24                                                           *
* Comment(s)    : Метод хорд поиска корней уравнения.                                *
*************************************************************************************/

/************************
* Подключение библиотек *
************************/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/****************
* Основное тело *
****************/
int main() {

    /* Установка точности числа после запятой */
    cout << fixed << setprecision(6);

    /* Определяем границы поиска и шаги */
    double start, end; // Начало и конец интервала
    double tol;
    int steps = 1000; // Количество частей деления интервала

    
    /* Вывод/ввод исходных данных */
    cout << "Нахождение корней методом Ньютона." << endl;
    cout << "Исходная функция y = (x0 * x0 * x0) - (2 * x * x) - (4 * x) + 7" << endl;
    cout << "Производная функции dy = (3 * x * x) - (4 * x) - 4 " << endl;
    cout << "Введите левую границу: ";
    cin >> start;

    if(double (start) == false){
        cout << "Ошибка: левая граница введена некоректно." << endl;
        exit(1);
    }
     
    cout << "Введите правую границу: ";
    cin >> end;

    if(double (end) == false){
        cout << "Ошибка: правая граница введена некоректно." << endl;
        exit(1);
    }

    cout << "Введите точность: ";
    cin >> tol;

    if(double (end) == false){
        cout << "Ошибка: правая граница введена некоректно.";
        exit(1);
    }

    /* Проверка ввода точности на > 1 */
    if(tol > 1) {
        cout << "Ошибка: Точность должна быть < 1.\n";
        exit(1);
    }

    /* Проверка ввода точности на < 0 */
    if(tol < 0) {
        cout << "Ошибка: Точность должна быть > 0.\n";
        exit(1);
    } 

    /* Проверка ввода точности на значение отличное от числа */
    if(double(tol) == false) {
        cout << "Ошибка: Введённое значение не является числом.\n";
        exit(1);
    }

    /* Поиск интервалов изменения знака функции */
    double intervals[1000][2]; // Массив для хранения интервалов, принимащий в себя 2 значения
    int interval_count = 0; // Счетчик интервалов
    double step = (end - start) / steps; // Просчёт нового шага
    double x_prev = start; // Задаём значение предыдущего x
    double y_prev = pow(x_prev, 3) - 2 * pow(x_prev, 2) - 4 * x_prev + 7; // Задаём значение предыдущего y с учётом ф-ции

    /* Цикл поиска значений, при которых функция меняет знак */
    for (int i = 1; i <= steps; ++i) {
        double x_curr = (start + i) * step; // Находим значение текущего x
        double y_curr = pow(x_curr, 3) - 2 * pow(x_curr, 2) - 4 * x_curr + 7; // Находим значение текущего y

        /* Проверка на изменение знака */
        if (y_prev * y_curr < 0) { 
            intervals[interval_count][0] = x_prev; // Начало интервала
            intervals[interval_count][1] = x_curr; // Конец интервала
            interval_count++; // Подсчёт количества интервалов
        }
        x_prev = x_curr; // Перезапись x
        y_prev = y_curr; // Перезапись y
    }

    /* Вывод интервалов смены знака */
    cout << endl << "Интервалы, где функция меняет знак:" << endl;
    for (int i = 0; i < interval_count; ++i) {
        cout << "[" << intervals[i][0] << ", " << intervals[i][1] << "]" << endl;
    }     
    cout << endl;

    /* Вывод знчений */
    for (int i = 0; i < interval_count; ++i) {
        double a = intervals[i][0]; // Перенос первого интервала в переменную
        double b = intervals[i][1]; // Перенос второго интервала в переменную
        cout << "Интервал: " << "[" << a << ", " << b << "]" << endl; // Вывод интервалов

        // Метод хорд (секущих)
        double x0 = a, x1 = b;  // Определение начальных значений ф-ций
        int max_iter = 100; // Максимальное число итераций
        int iter_secant = 0; // Переменная подсчёта количество итераций метода секущих
        double root_secant = NAN;

        /* Подсчёт значения функции по методу секущих */
        for (int j = 0; j < max_iter; ++j) {
            double fx0 = pow(x0, 3) - 2 * pow(x0, 2) - 4 * x0 + 7; // Значение функции по x0
            double fx1 = pow(x1, 3) - 2 * pow(x1, 2) - 4 * x1 + 7; // Значение функции по x1
            if (fabs(fx1 - fx0) < 1e-12) break; // предотвращение деления на ноль
            double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0); // Нахождения x2
            /* Проверка на достижение необходимой точности */
            if (fabs(pow(x2, 3) - 2 * pow(x2, 2) - 4 * x2 + 7) < tol) { 
                root_secant = x2;
                iter_secant = j + 1;
                break;
            }
            x0 = x1; // Перезапись x0
            x1 = x2; // Перезапись x1
        }

        // Метод Ньютона
        double x_newton = (a + b) / 2; // Нахождение начального значения x по методу ньютона
        int iter_newton = 0; // Переменная подсчёта количества итераций по методу ньютона
        double root_newton = NAN;

        /* Подсчёт значения функции по методу ньютона */
        for (int j = 0; j < max_iter; ++j) {
            double fx0 = pow(x_newton, 3) - 2 * pow(x_newton, 2) - 4 * x_newton + 7; // Подсчёт значения ф-ции от x0 по методу ньютона
            double dfx0 = 3 * pow(x_newton, 2) - 4 * x_newton - 4; // Подсчёт значения дифференциала ф-ции от x0 по методу ньютона
            if (fabs(dfx0) < 1e-12) break; // предотвращение деления на ноль
            double x1 = x_newton - fx0 / dfx0; // Нахождение x1
            /* Проверка на достижение необходимой точности */
            if (fabs(pow(x1, 3) - 2 * pow(x1, 2) - 4 * x1 + 7) < tol) {
                root_newton = x1;
                iter_newton = j + 1;
                break;
            }
            x_newton = x1; // Перезапись x
        }

        /* Вывод полученных значений */
        cout << "  Метод Хорд: корень = " << root_secant << ", итерации = " << iter_secant << "\n";
        cout << "  Метод Ньютона: корень = " << root_newton << ", итерации = " << iter_newton << "\n";
    }

    return 0;
}
