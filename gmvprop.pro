QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = gmvprop
TEMPLATE = app
SOURCES = main.cpp app.cpp gmv.c
HEADERS = app.h gmv.h
FORMS = app.ui
