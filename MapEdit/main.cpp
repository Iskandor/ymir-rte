/*
 * File:   main.cpp
 * Author: matej
 *
 * Created on October 8, 2012, 6:57 PM
 */

#include <QtGui/QApplication>
#include <qt4/QtGui/qwidget.h>
#include "Forms/EntryForm.h"

#include "CModule.h" 

int main(int argc, char *argv[]) {
  // initialize resources, if needed
  // Q_INIT_RESOURCE(resfile);
  
  QApplication app(argc, argv);

  // create and show your widgets here

  EntryForm fMain;

  fMain.show();

  return app.exec();
}
