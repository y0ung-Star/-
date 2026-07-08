/****************************************************************
*                     КАФЕДРА № 304 2 КУРС                       *
*---------------------------------------------------------------*
* Project Type  : Qt Widgets Desktop Application                *
* Project Name  : FieldViz                                      *
* File Name     : FieldMath.cpp                                  *
* Language      : C/C++ (C++17)                                  *
* Programmer(s) : Егоров А.В. (swrneko)                          *
* Modifyed By   : Егоров А.В. (swrneko)                          *
* Edited by     : Neovim                                         *
* OS            : Arch Linux                                     *
* Created       : 01/07/26                                       *
* Last Revision : 01/07/26                                       *
* Comment(s)    : Реализация расчёта векторных полей.            *
****************************************************************/

#include "FieldMath.h"
#include <cmath>

/****************************************
* Вспомогательная функция нормализации  *
****************************************/
static Point3D getDirA(double x, double y, double z) {
  double ax, ay, az; // Векторы поля
  FieldMath::getFieldA(x, y, z, ax, ay, az); // Получение поля

  double len = std::sqrt(ax * ax + ay * ay + az * az); // Длина вектора
  if (len < 1e-9) { // Проверка на ноль
    return Point3D(0, 0, 0); // Нулевой вектор
  }

  return Point3D(ax / len, ay / len, az / len); // Возврат нормали
}

/****************************************
* Расчёт векторного поля a (Вариант 5)  *
****************************************/
void FieldMath::getFieldA(double x, double y, double z, double &ax, double &ay, double &az) {
  ax = y * y; // a_x = y^2
  ay = z * z; // a_y = z^2
  az = x * x; // a_z = x^2
}

/****************************************
* Расчёт векторного поля b (Вариант 5)  *
****************************************/
void FieldMath::getFieldB(double x, double y, double z, double &bx, double &by, double &bz) {
  bx = 2.0 * x * y * y * y * z + y; // b_x = 2xy^3z + y
  by = 3.0 * x * x * y * y * z + x; // b_y = 3x^2y^2z + x
  bz = x * x * y * y * y + 4.0 * z * z * z; // b_z = x^2y^3 + 4z^3
}

/****************************************
* Расчёт потенциала поля b (Вариант 5)  *
****************************************/
double FieldMath::getPotentialU(double x, double y, double z) {
  return x * y + x * x * y * y * y * z + z * z * z * z; // U = xy + x^2y^3z + z^4
}

/****************************************************************
* Численное интегрирование силовой линии (метод Рунге-Кутты 4)   *
****************************************************************/
std::vector<Point3D> FieldMath::buildFieldLine(double sx, double sy, double sz, double step, int max_steps) {
  std::vector<Point3D> line; // Хранилище точек линии
  Point3D curr(sx, sy, sz); // Начальная точка

  line.push_back(curr); // Запись старта

  for (int i = 0; i < max_steps; ++i) { // Цикл шагов
    Point3D k1 = getDirA(curr.x, curr.y, curr.z); // Шаг 1
    if (k1.x == 0 && k1.y == 0 && k1.z == 0) break; // Останов на нуле

    Point3D p2(curr.x + 0.5 * step * k1.x, curr.y + 0.5 * step * k1.y, curr.z + 0.5 * step * k1.z); // Точка 2
    Point3D k2 = getDirA(p2.x, p2.y, p2.z); // Шаг 2

    Point3D p3(curr.x + 0.5 * step * k2.x, curr.y + 0.5 * step * k2.y, curr.z + 0.5 * step * k2.z); // Точка 3
    Point3D k3 = getDirA(p3.x, p3.y, p3.z); // Шаг 3

    Point3D p4(curr.x + step * k3.x, curr.y + step * k3.y, curr.z + step * k3.z); // Точка 4
    Point3D k4 = getDirA(p4.x, p4.y, p4.z); // Шаг 4

    curr.x += (step / 6.0) * (k1.x + 2.0 * k2.x + 2.0 * k3.x + k4.x); // Новый X
    curr.y += (step / 6.0) * (k1.y + 2.0 * k2.y + 2.0 * k3.y + k4.y); // Новый Y
    curr.z += (step / 6.0) * (k1.z + 2.0 * k2.z + 2.0 * k3.z + k4.z); // Новый Z

    // Проверка выхода из первого октанта единичной сферы
    double dist2 = curr.x * curr.x + curr.y * curr.y + curr.z * curr.z; // Квадрат расстояния
    if (dist2 > 1.2 || curr.x < -0.1 || curr.y < -0.1 || curr.z < -0.1) { // Условие выхода
      break; // Выход из цикла
    }

    line.push_back(curr); // Запись точки
  }

  return line; // Возврат линии
}
