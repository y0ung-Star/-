# ================================================================
#                     КАФЕДРА № 304 2 КУРС
# ---------------------------------------------------------------
# Project Type  : Qt Widgets Desktop Application
# Project Name  : FieldViz
# File Name     : FieldViz.pro
# Language      : QMake Script
# Programmer(s) : Егоров А.В. (swrneko)
# Modifyed By   : Егоров А.В. (swrneko)
# Edited by     : Neovim
# OS            : Arch Linux
# Created       : 01/07/26
# Last Revision : 01/07/26
# Comment(s)    : Сборочный файл проекта QMake.
# ================================================================

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = FieldViz
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Visualizer.cpp \
    FieldMath.cpp

HEADERS += \
    MainWindow.h \
    Visualizer.h \
    FieldMath.h
