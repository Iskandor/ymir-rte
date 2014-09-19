/* 
 * File:   NewProjModuleDlh.h
 * Author: matej
 *
 * Created on September 17, 2014, 8:45 PM
 */

#ifndef NEWPROJMODULEDLG_H
#define	NEWPROJMODULEDLG_H

#include "ui_NewProjModuleDlg.h"
#include "CModule.h"
#include "CProjectile.h"

#include <qt4/QtGui/QStandardItemModel>
#include <QPixmap>

class NewProjModuleDlg : public QDialog {
  Q_OBJECT
public:
  NewProjModuleDlg();
  virtual ~NewProjModuleDlg();
private:
  Ui::NewProjModuleDlg widget;
  
  CModule<CProjectile> *projectile_module;
  CProjectile           projectile_model;
  QPixmap*          projectile_image; 
  
  QStandardItemModel* listview_model;
  int                 selected_id;
  
private:
  void DrawImage();
  void RefreshListView();
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
  
  void SizeXChanged(int val);
  void SizeYChanged(int val);    
};

#endif	/* NEWPROJMODULEDLH_H */

