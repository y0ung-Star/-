/****************************************************************
*                     КАФЕДРА № 304 2 КУРС                       *
*---------------------------------------------------------------*
* Project Type  : Qt Widgets Desktop Application                *
* Project Name  : FieldViz                                      *
* File Name     : Visualizer.cpp                                 *
* Language      : C/C++ (C++17)                                  *
* Programmer(s) : Егоров А.В. (swrneko)                          *
* Modifyed By   : Егоров А.В. (swrneko)                          *
* Edited by     : Neovim                                         *
* OS            : Arch Linux                                     *
* Created       : 01/07/26                                       *
* Last Revision : 01/07/26                                       *
* Comment(s)    : Реализация функций 3D отрисовки сцены.         *
****************************************************************/

#include "Visualizer.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <cmath>
#include <algorithm>

/****************************************
* Конструктор и базовые настройки       *
****************************************/
Visualizer::Visualizer(QWidget *parent)
  : QWidget(parent), m_yaw(30.0), m_pitch(30.0), m_zoom(1.0),
    m_showFieldLines(true), m_showEquipotentials(true) {
  setMinimumSize(400, 400); // Минимальный размер виджета
  setBackgroundRole(QPalette::Base); // Роль фона
  setAutoFillBackground(true); // Заливка фона
}

/****************************************
* Управление флагами отрисовки          *
****************************************/
void Visualizer::setShowFieldLines(bool show) {
  m_showFieldLines = show; // Установка флага
  update(); // Обновление окна
}

void Visualizer::setShowEquipotentials(bool show) {
  m_showEquipotentials = show; // Установка флага
  update(); // Обновление окна
}

void Visualizer::resetCamera() {
  m_yaw = 30.0; // Сброс yaw
  m_pitch = 30.0; // Сброс pitch
  m_zoom = 1.0; // Сброс zoom
  update(); // Обновление окна
}

/****************************************
* Проекция 3D точки на 2D экран         *
****************************************/
QPointF Visualizer::project(const Point3D &p, int width, int height) const {
  double rad_yaw = m_yaw * M_PI / 180.0; // Перевод yaw в радианы
  double rad_pitch = m_pitch * M_PI / 180.0; // Перевод pitch в радианы

  // Поворот вокруг оси Z (Yaw)
  double x1 = p.x * std::cos(rad_yaw) - p.y * std::sin(rad_yaw);
  double y1 = p.x * std::sin(rad_yaw) + p.y * std::cos(rad_yaw);
  double z1 = p.z;

  // Поворот вокруг оси X (Pitch)
  double x2 = x1;
  double y2 = y1 * std::cos(rad_pitch) - z1 * std::sin(rad_pitch);

  // Центрирование и масштаб
  double scale = std::min(width, height) * 0.35 * m_zoom;
  double sx = width / 2.0 + x2 * scale;
  double sy = height / 2.0 - y2 * scale; // Инверсия Y экрана

  return QPointF(sx, sy);
}

/****************************************
* Отрисовка координатных осей           *
****************************************/
void Visualizer::drawAxes(QPainter &painter, int w, int h) {
  QPointF origin = project(Point3D(0, 0, 0), w, h); // Начало координат

  // Ось X (Красная)
  painter.setPen(QPen(Qt::red, 2)); // Перо
  painter.drawLine(origin, project(Point3D(1.3, 0, 0), w, h)); // Линия
  painter.drawText(project(Point3D(1.4, 0, 0), w, h), "X"); // Подпись

  // Ось Y (Зелёная)
  painter.setPen(QPen(Qt::darkGreen, 2)); // Перо
  painter.drawLine(origin, project(Point3D(0, 1.3, 0), w, h)); // Линия
  painter.drawText(project(Point3D(0, 1.4, 0), w, h), "Y"); // Подпись

  // Ось Z (Синяя)
  painter.setPen(QPen(Qt::blue, 2)); // Перо
  painter.drawLine(origin, project(Point3D(0, 0, 1.3), w, h)); // Линия
  painter.drawText(project(Point3D(0, 0, 1.4), w, h), "Z"); // Подпись
}

/****************************************
* Отрисовка каркаса сферы               *
****************************************/
void Visualizer::drawSphereWireframe(QPainter &painter, int w, int h) {
  painter.setPen(QPen(QColor(180, 180, 180, 150), 1, Qt::DashLine)); // Настройка пера

  // Широты (параллели) сферы
  for (int t_deg = 0; t_deg <= 90; t_deg += 15) {
    double theta = t_deg * M_PI / 180.0; // В радианы
    QPointF p_prev = project(Point3D(std::sin(theta), 0, std::cos(theta)), w, h); // Предыдущая
    for (int p_deg = 3; p_deg <= 90; p_deg += 3) {
      double phi = p_deg * M_PI / 180.0; // В радианы
      Point3D pt(std::sin(theta) * std::cos(phi), std::sin(theta) * std::sin(phi), std::cos(theta)); // Точка
      QPointF p_curr = project(pt, w, h); // Спроецированная
      painter.drawLine(p_prev, p_curr); // Рисование отрезка
      p_prev = p_curr; // Сдвиг
    }
  }

  // Долготы (меридианы) сферы
  for (int p_deg = 0; p_deg <= 90; p_deg += 15) {
    double phi = p_deg * M_PI / 180.0; // В радианы
    QPointF p_prev = project(Point3D(0, 0, 1), w, h); // Старт на полюсе Z
    for (int t_deg = 3; t_deg <= 90; t_deg += 3) {
      double theta = t_deg * M_PI / 180.0; // В радианы
      Point3D pt(std::sin(theta) * std::cos(phi), std::sin(theta) * std::sin(phi), std::cos(theta)); // Точка
      QPointF p_curr = project(pt, w, h); // Спроецированная
      painter.drawLine(p_prev, p_curr); // Рисование отрезка
      p_prev = p_curr; // Сдвиг
    }
  }
}

/****************************************
* Отрисовка силовых линий поля a        *
****************************************/
void Visualizer::drawFieldLines(QPainter &painter, int w, int h) {
  if (!m_showFieldLines) return; // Проверка флага

  painter.setPen(QPen(Qt::darkCyan, 2)); // Перо для силовых линий

  // Точки запуска линий (seeds)
  std::vector<Point3D> seeds = {
    Point3D(0.1, 0.1, 0.1), Point3D(0.3, 0.3, 0.3),
    Point3D(0.5, 0.5, 0.5), Point3D(0.7, 0.7, 0.7),
    Point3D(0.2, 0.5, 0.2), Point3D(0.5, 0.2, 0.5),
    Point3D(0.1, 0.8, 0.1), Point3D(0.8, 0.1, 0.1)
  };

  for (const auto &seed : seeds) { // Проход по всем семенам
    auto line = FieldMath::buildFieldLine(seed.x, seed.y, seed.z, 0.015, 120); // Расчёт линии
    if (line.size() < 2) continue; // Пропуск коротких

    QPointF p_prev = project(line[0], w, h); // Предыдущая
    for (size_t i = 1; i < line.size(); ++i) { // Отрисовка по сегментам
      QPointF p_curr = project(line[i], w, h); // Текущая
      painter.drawLine(p_prev, p_curr); // Линия
      p_prev = p_curr; // Сдвиг
    }
  }
}

/****************************************
* Отрисовка эквипотенциалей поля b      *
****************************************/
void Visualizer::drawEquipotentials(QPainter &painter, int w, int h) {
  if (!m_showEquipotentials) return; // Проверка флага

  painter.setPen(QPen(Qt::magenta, 1, Qt::SolidLine)); // Розовый цвет для U = const

  // Константные уровни потенциала C для отрисовки
  std::vector<double> levels = {0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5};

  // Отрисовка эквипотенциалей в плоскости xy (z = 0 -> U = xy = C)
  for (double C : levels) {
    QPointF p_prev; // Точка старта
    bool first = true; // Флаг первой точки
    for (double x = C; x <= 1.0; x += 0.02) { // Построение гиперболы y = C / x
      double y = C / x; // Вычисление Y
      if (y > 1.0) continue; // Ограничение
      QPointF p_curr = project(Point3D(x, y, 0), w, h); // Проекция
      if (!first) painter.drawLine(p_prev, p_curr); // Отрисовка
      p_prev = p_curr; // Сдвиг
      first = false; // Сброс флага
    }
  }

  // Отрисовка на самой сфере методом сканирования сетки
  // Если изоуровень C находится между вершинами ячейки сферы, рисуем отрезок
  for (double C : levels) {
    for (int t_deg = 0; t_deg < 90; t_deg += 3) {
      double theta = t_deg * M_PI / 180.0;
      double theta_next = (t_deg + 3) * M_PI / 180.0;
      for (int p_deg = 0; p_deg < 90; p_deg += 3) {
        double phi = p_deg * M_PI / 180.0;
        double phi_next = (p_deg + 3) * M_PI / 180.0;

        // Координаты 4-х вершин ячейки сферы
        Point3D v00(std::sin(theta)*std::cos(phi), std::sin(theta)*std::sin(phi), std::cos(theta));
        Point3D v10(std::sin(theta_next)*std::cos(phi), std::sin(theta_next)*std::sin(phi), std::cos(theta_next));
        Point3D v01(std::sin(theta)*std::cos(phi_next), std::sin(theta)*std::sin(phi_next), std::cos(theta));

        // Потенциалы в вершинах
        double u00 = FieldMath::getPotentialU(v00.x, v00.y, v00.z);
        double u10 = FieldMath::getPotentialU(v10.x, v10.y, v10.z);
        double u01 = FieldMath::getPotentialU(v01.x, v01.y, v01.z);

        // Линейная интерполяция изолинии C
        if ((u00 <= C && u10 >= C) || (u00 >= C && u10 <= C)) {
          double t = (C - u00) / (u10 - u00);
          Point3D pt(v00.x + t*(v10.x - v00.x), v00.y + t*(v10.y - v00.y), v00.z + t*(v10.z - v00.z));
          painter.drawPoint(project(pt, w, h));
        }
        if ((u00 <= C && u01 >= C) || (u00 >= C && u01 <= C)) {
          double t = (C - u00) / (u01 - u00);
          Point3D pt(v00.x + t*(v01.x - v00.x), v00.y + t*(v01.y - v00.y), v00.z + t*(v01.z - v00.z));
          painter.drawPoint(project(pt, w, h));
        }
      }
    }
  }
}

/****************************************
* Обработчик события рисования виджета  *
****************************************/
void Visualizer::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event); // Избегаем предупреждения компилятора
  QPainter painter(this); // Инициализация рисовальщика
  painter.setRenderHint(QPainter::Antialiasing); // Сглаживание линий

  int w = width(); // Ширина окна
  int h = height(); // Высота окна

  // Очистка фона (белый цвет)
  painter.fillRect(rect(), Qt::white);

  drawAxes(painter, w, h); // 1. Отрисовка осей координат
  drawSphereWireframe(painter, w, h); // 2. Отрисовка сетки сферы
  drawFieldLines(painter, w, h); // 3. Отрисовка силовых линий
  drawEquipotentials(painter, w, h); // 4. Отрисовка эквипотенциалей
}

/****************************************
* Обработка событий мыши                *
****************************************/
void Visualizer::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) { // Проверка ЛКМ
    m_lastMousePos = event->pos(); // Сохранение позиции клика
  }
}

void Visualizer::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) { // Перетаскивание ЛКМ
    int dx = event->x() - m_lastMousePos.x(); // Смещение по X
    int dy = event->y() - m_lastMousePos.y(); // Смещение по Y

    m_yaw += dx * 0.5; // Изменение yaw
    m_pitch += dy * 0.5; // Изменение pitch

    m_lastMousePos = event->pos(); // Обновление позиции
    update(); // Перерисовка окна
  }
}

void Visualizer::wheelEvent(QWheelEvent *event) {
  double numDegrees = event->angleDelta().y() / 8.0; // Угол поворота колеса
  double numSteps = numDegrees / 15.0; // Число шагов

  m_zoom += numSteps * 0.1; // Изменение зума
  m_zoom = std::clamp(m_zoom, 0.2, 5.0); // Ограничение диапазона

  update(); // Перерисовка окна
}
