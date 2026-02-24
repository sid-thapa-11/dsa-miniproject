QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = StudentRecordSystem
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    linkedlist.cpp \
    bst.cpp \
    sortingalgorithms.cpp \
    undostack.cpp

HEADERS += \
    mainwindow.h \
    student.h \
    linkedlist.h \
    bst.h \
    sortingalgorithms.h \
    undostack.h

FORMS += \
    mainwindow.ui
