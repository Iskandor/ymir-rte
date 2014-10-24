# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = MapEdit
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui xml
SOURCES += CMapRender.cpp Forms/EntryForm.cpp Forms/NewMapDlg.cpp Forms/NewObjectModuleDlg.cpp Forms/NewTileModuleDlg.cpp Forms/NewUnitModuleDlg.cpp NewModifModuleDlg.cpp NewProjModuleDlg.cpp main.cpp src/CObjectClass.cpp src/QClickLabel.cpp
HEADERS += CMapRender.h Forms/EntryForm.h Forms/NewMapDlg.h Forms/NewObjectModuleDlg.h Forms/NewTileModuleDlg.h Forms/NewUnitModuleDlg.h NewModifModuleDlg.h NewProjModuleDlg.h include/CObjectClass.h include/QClickLabel.h
FORMS += Forms/EntryForm.ui Forms/NewMapDlg.ui Forms/NewObjectModuleDlg.ui Forms/NewProjModuleDlg.ui Forms/NewTileModuleDlg.ui Forms/NewUnitModuleDlg.ui NewModifModuleDlg.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../YmirCore/include /usr/include/qt4 include 
LIBS += -Wl,-rpath,../YmirCore/bin ../YmirCore/bin/libYmirCore.so  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
