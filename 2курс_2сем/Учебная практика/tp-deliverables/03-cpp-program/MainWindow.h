/****************************************************************
*                     КАФЕДРА № 304 2 КУРС                       *
*---------------------------------------------------------------*
* Project Type  : Qt Widgets Desktop Application                *
* Project Name  : FieldViz                                      *
* File Name     : MainWindow.h                                   *
* Language      : C/C++ (C++17)                                  *
* Programmer(s) : Егоров А.В. (swrneko)                          *
* Modifyed By   : Егоров А.В. (swrneko)                          *
* Edited by     : Neovim                                         *
* OS            : Arch Linux                                     *
* Created       : 01/07/26                                       *
* Last Revision : 01/07/26                                       *
* Comment(s)    : Главное окно GUI приложения.                   *
****************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Visualizer.h"

class QCheckBox;
class QPushButton;
class QLabel;

/****************************************************************
* Класс главного окна приложения                                *
****************************************************************/
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  // Конструктор главного окна
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
  // Слот переключения видимости силовых линий
  void onFieldLinesToggled(bool checked);

  // Слот переключения видимости эквипотенциалей
  void onEquipotentialsToggled(bool checked);

  // Слот сброса положения камеры
  void onResetCameraClicked();

private:
  Visualizer *m_visualizer;       // Виджет 3D-визуализации
  QCheckBox *m_chkFieldLines;     // Чекбокс силовых линий
  QCheckBox *m_chkEquipotentials; // Чекбокс эквипотенциалей
  QPushButton *m_btnResetCamera;  // Кнопка сброса камеры
  QLabel *m_lblInfoPanel;         // Текстовая панель результатов (Solver)

  // Инициализация интерфейса
  void setupUi();
};

#endif // MAINWINDOW_H
