/*******************************************************************
*                       КАФЕДРА № 304 1 КУРС                       *
*------------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                    *
* Project Name  : laba_0                                           *
* File Name     : main.cpp                                         *
* Language      : C/C++                                            *
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И, Трифанов А.Л. *
* Modifyed By   : Егоров А.В (swrneko)                             *
* Edited by     : Neovim, Visual Studio, Sublime Text              *
* OS            : Arch Linux, Windows 11/10                        *
* Github url    : https://github.com/swrneko/mai_shit.git          *
* Created       : 24.12/24                                         *
* Last Revision : 24/12/24                                         *
* Comment(s)    : Метод хорд поиска корней уравнения.              *
*******************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;


// double f(double x) {
//   return (pow(x,3) - 2*(pow(x,2)) - (4*x) + 7);
// }
//
// double df(double x) {
//   return (3*(pow(x, 2)) - (4*x) - 4);
// }
//
// double secant_method(double x0, double x1, double tol, double max_iter) {
//   double iter_count = 0;
//   while(fabs(x1 - x0) >= tol && iter_count < max_iter) {
//     double x_temp = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
//     x0 = x1;
//     x1 = x_temp;
//     iter_count += 1;
//   return x1, iter_count;
//   }
// }

int main() {
    // Определяем границы поиска и шаги
    double x;
    double x0 = -3.0;
    double x1 = 3.0;
    double tol;
    int max_iter = 1000;
    int iter_count = 0;


    double f =  (pow(x,3) - 2*(pow(x,2)) - (4*x) + 7);
    double df = (3*(pow(x, 2)) - (4*x) - 4);
    
    while(fabs(x1 - x0) >= tol && iter_count < max_iter) {
      double x_temp = x1 - (pow(x1,3) - 2*(pow(x1,2)) - (4*x1) + 7) * (x1 - x0) / ((pow(x1,3) - 2*(pow(x1,2)) - (4*x1) + 7) - (pow(x0,3) - 2*(pow(x0,2)) - (4*x0) + 7));
      x0 = x1;
      x1 = x_temp;
      iter_count += 1;
    }


}
