/****************************************************************
*                     КАФЕДРА № 304 2 КУРС                       *
*---------------------------------------------------------------*
* Project Type  : Qt Widgets Desktop Application                *
* Project Name  : FieldViz                                      *
* File Name     : FieldMath.h                                    *
* Language      : C/C++ (C++17)                                  *
* Programmer(s) : Егоров А.В. (swrneko)                          *
* Modifyed By   : Егоров А.В. (swrneko)                          *
* Edited by     : Neovim                                         *
* OS            : Arch Linux                                     *
* Created       : 01/07/26                                       *
* Last Revision : 01/07/26                                       *
* Comment(s)    : Математические функции расчёта полей.          *
****************************************************************/

#ifndef FIELDMATH_H
#define FIELDMATH_H

#include <vector>

/******************************************
* Структура для представления точки в 3D *
******************************************/
struct Point3D {
  double x; // Координата X
  double y; // Координата Y
  double z; // Координата Z

  // Конструктор по умолчанию
  Point3D() : x(0), y(0), z(0) {}

  // Конструктор инициализации
  Point3D(double px, double py, double pz) : x(px), y(py), z(pz) {}
};

/************************************
* Класс математических расчётов полей*
************************************/
class FieldMath {
public:
  // Расчёт векторного поля a
  static void getFieldA(double x, double y, double z, double &ax, double &ay, double &az);

  // Расчёт векторного поля b
  static void getFieldB(double x, double y, double z, double &bx, double &by, double &bz);

  // Расчёт потенциала поля b
  static double getPotentialU(double x, double y, double z);

  // Численное построение силовой линии поля a (метод Рунге-Кутты 4 порядка)
  static std::vector<Point3D> buildFieldLine(double sx, double sy, double sz, double step, int max_steps);
};

#endif // FIELDMATH_H
