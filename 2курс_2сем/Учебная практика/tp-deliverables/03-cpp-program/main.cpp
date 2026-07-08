/****************************************************************
*                     КАФЕДРА № 304 2 КУРС                       *
*---------------------------------------------------------------*
* Project Type  : Qt Widgets Desktop Application                *
* Project Name  : FieldViz                                      *
* File Name     : main.cpp                                       *
* Language      : C/C++ (C++17)                                  *
* Programmer(s) : Егоров А.В. (swrneko)                          *
* Modifyed By   : Егоров А.В. (swrneko)                          *
* Edited by     : Neovim                                         *
* OS            : Arch Linux                                     *
* Created       : 01/07/26                                       *
* Last Revision : 01/07/26                                       *
* Comment(s)    : Точка входа в программу.                       *
****************************************************************/

#include <QApplication>
#include "MainWindow.h"

/****************************************
* Главная функция запуска программы     *
****************************************/
int main(int argc, char *argv[]) {
  QApplication app(argc, argv); // Инициализация Qt-приложения

  MainWindow window; // Создание главного окна
  window.show(); // Отображение главного окна

  return app.exec(); // Запуск цикла обработки событий Qt
}
