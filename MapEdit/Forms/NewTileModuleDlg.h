/* 
 * File:   NewTileModuleDlg.h
 * Author: matej
 *
 * Created on October 31, 2013, 5:47 PM
 */

#ifndef _NEWTILEMODULEDLG_H
#define	_NEWTILEMODULEDLG_H

#include "ui_NewTileModuleDlg.h"
#include "CTile.h"
#include "CModule.h"

#include <qt4/QtGui/QStandardItemModel>

class NewTileModuleDlg : public QDialog {
  Q_OBJECT
public:
  NewTileModuleDlg();
  virtual ~NewTileModuleDlg();
  
private:
  Ui::NewTileModuleDlg widget;
  
  CModule<CTile>*     tile_module;
  CTile               tile_model;
  QStandardItemModel* listview_model;
  int                 selected_id;
  
public slots:
  void accept();
  void addTile();
  void editTile();
  void removeTile();
  void saveTile();
  void chooseFile();  
  
private:
  void ModelToForm();
  void FormToModel();
  
  void RefreshListView();
  void RefreshImage(QString filename);  
};

#endif	/* _NEWTILEMODULEDLG_H */
