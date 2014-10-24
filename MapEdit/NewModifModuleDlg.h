/* 
 * File:   NewModifModuleDlg.h
 * Author: Matej Pechac
 *
 * Created on October 1, 2014, 10:04 PM
 */

#ifndef _NEWMODIFMODULEDLG_H
#define	_NEWMODIFMODULEDLG_H

#include "ui_NewModifModuleDlg.h"
#include "CModifier.h"
#include "CModule.h"
#include "CObjectClass.h"

#include <qt4/QtGui/QStandardItemModel>

class NewModifModuleDlg : public QDialog {
  Q_OBJECT
public:
  NewModifModuleDlg();
  virtual ~NewModifModuleDlg();
private:
  Ui::NewModifModuleDlg widget;
  
  CModule<CModifier> *modifier_module;
  CModifier           modifier_model;
  CObjectClass        object_class;
  
  QStandardItemModel* listview_model;
  int                 selected_id;
  
private:
  void RefreshListView();
  void RefreshComboBox();
  
  void FormToModel();
  void ModelToForm();  
  
public slots:
  void accept();
  void addObject();
  void editObject();
  void removeObject();
  void saveObject();  
};


#endif	/* _NEWMODIFMODULEDLG_H */
