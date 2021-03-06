/* 
 * File:   NewObjectModuleDlg.h
 * Author: Matej Pechac
 *
 * Created on May 10, 2014, 2:33 PM
 */

#ifndef _NEWOBJECTMODULEDLG_H
#define	_NEWOBJECTMODULEDLG_H

#include "ui_NewObjectModuleDlg.h"
#include "CModule.h"
#include "CObject.h"
#include "CObjectClass.h"

#include <qt4/QtGui/QStandardItemModel>
#include <QPixmap>

class NewObjectModuleDlg : public QDialog {
  Q_OBJECT
public:
  NewObjectModuleDlg();
  virtual ~NewObjectModuleDlg();
private:
  Ui::NewObjectModuleDlg widget;
  
  CModule<CObject> *object_module;
  CObject           object_model;
  QPixmap*          object_image; 
  
  QStandardItemModel* listview_model;
  CObjectClass        object_class;
  int                 selected_id;
  
private:
  void DrawImage();
  void RefreshListView();
  void RefreshComboBox();
  void RefreshImage(QString _filename);
  void DrawGrid(QPixmap* pixmap);
  
  void FormToModel();
  void ModelToForm();  
  
public slots:
  void accept();
  void addObject();
  void editObject();
  void removeObject();
  void saveObject();
  void chooseFile();
  void imageOnclick();
  void ChangeClass(int val);
  
  void SizeXChanged(int val);
  void SizeYChanged(int val);    
};

#endif	/* _NEWOBJECTMODULEDLG_H */
