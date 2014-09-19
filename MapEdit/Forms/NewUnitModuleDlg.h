/* 
 * File:   NewUnitModuleDlg.h
 * Author: Matej Pechac
 *
 * Created on June 30, 2013, 4:33 PM
 */

#ifndef _NEWUNITMODULEDLG_H
#define	_NEWUNITMODULEDLG_H

#include "ui_NewUnitModuleDlg.h"
#include "CModule.h"
#include "CUnit.h"
#include "CRace.h"
#include "CProjectile.h"

#include <qt4/QtGui/QStandardItemModel>
#include <qt4/QtGui/QStringListModel>
#include <QPixmap>

class NewUnitModuleDlg : public QDialog {
  Q_OBJECT
public:
  NewUnitModuleDlg();
  virtual ~NewUnitModuleDlg();
  
private:
  void FormToModel();
  void ModelToForm();
  void RefreshListView();
  void RefreshComboBox();
  void DrawImage();
  void RefreshImage(QString _filename);
  void DrawGrid(QPixmap* pixmap);
  
private:
  Ui::NewUnitModuleDlg widget;
  
  CModule<CUnit>*       unit_module;
  CModule<CProjectile>  projectile_module;
  CUnit                 unit_model;
  CRace*                race_list;
  QPixmap*              unit_image; 
  
  QStandardItemModel* listview_model;
  int                 selected_id;
  
  
public slots:
  void accept();
  void addUnit();
  void editUnit();
  void removeUnit();
  void saveUnit();
  void chooseFile();
  void imageOnclick();
  
  void SizeXChanged(int val);
  void SizeYChanged(int val);  
};

#endif	/* _NEWUNITMODULEDLG_H */
