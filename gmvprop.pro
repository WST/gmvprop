QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = gmvprop
TEMPLATE = app
SOURCES = src/main.cpp src/app.cpp src/gmv.c
HEADERS = src/app.h src/gmv.h
FORMS = ui/app.ui
DESTDIR = bin
MOC_DIR = build
OBJECTS_DIR = build
RCC_DIR = build
UI_DIR = build

RESOURCES += \
    res/resources.qrc
