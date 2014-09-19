# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = MapEdit
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui
SOURCES += CMapRender.cpp Forms/EntryForm.cpp Forms/NewMapDlg.cpp Forms/NewObjectModuleDlg.cpp Forms/NewTileModuleDlg.cpp Forms/NewUnitModuleDlg.cpp NewProjModuleDlg.cpp main.cpp src/CObjectClass.cpp src/QClickLabel.cpp
HEADERS += CMapRender.h Forms/EntryForm.h Forms/NewMapDlg.h Forms/NewObjectModuleDlg.h Forms/NewTileModuleDlg.h Forms/NewUnitModuleDlg.h NewProjModuleDlg.h include/CObjectClass.h include/QClickLabel.h
FORMS += Forms/EntryForm.ui Forms/NewMapDlg.ui Forms/NewObjectModuleDlg.ui Forms/NewProjModuleDlg.ui Forms/NewTileModuleDlg.ui Forms/NewUnitModuleDlg.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
