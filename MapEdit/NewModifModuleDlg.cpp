/*
 * File:   NewModifModuleDlg.cpp
 * Author: Matej Pechac
 *
 * Created on October 1, 2014, 10:04 PM
 */

#include "NewModifModuleDlg.h"
#include "GlobalDefine.h"

NewModifModuleDlg::NewModifModuleDlg() {
  widget.setupUi(this);
  
  connect(widget.bAdd, SIGNAL(clicked()), this, SLOT(addObject()));
  connect(widget.bEdit, SIGNAL(clicked()), this, SLOT(editObject()));
  connect(widget.bDelete, SIGNAL(clicked()), this, SLOT(removeObject()));
  connect(widget.bSave, SIGNAL(clicked()), this, SLOT(saveObject()));

  modifier_module = new CModule<CModifier>();
  modifier_module->LoadFromXML("data/modifiers", "modifiers", "modifier");
  widget.leModuleName->setText(MODIFIER_LIST);
  
  listview_model = new QStandardItemModel();
  object_class.LoadFromXML("data/modif_classes");
  
  RefreshListView();
  RefreshComboBox();
}

NewModifModuleDlg::~NewModifModuleDlg() {
  delete modifier_module;
  delete listview_model;
}

void NewModifModuleDlg::accept() {
  modifier_module->SaveToXML(string("modifiers"), string("modifier"));
  QDialog::accept();  
}

void NewModifModuleDlg::RefreshListView() {
  listview_model->clear();
  

  for(int i = 0; i < modifier_module->GetSize(); i++) {
    QStandardItem *item = new QStandardItem(QString(modifier_module->GetUnit(i).GetDesc().c_str()));   
    listview_model->appendRow(item);
  }

  widget.ObjectList->setModel(listview_model);  
}

void NewModifModuleDlg::RefreshComboBox() {
  widget.cbClass->clear();
        
  for(map<int, string>::iterator it = object_class.getClasses()->begin(); it != object_class.getClasses()->end(); it++) {
    pair<int, string> obj_class = *it;
    widget.cbClass->addItem(QString(obj_class.second.c_str()), QVariant(obj_class.first));
  }  

}

void NewModifModuleDlg::addObject() {
  FormToModel();
  modifier_module->AddUnit(modifier_model);
  RefreshListView();
  
  return;
}

void NewModifModuleDlg::editObject() {
  int selected = widget.ObjectList->selectionModel()->currentIndex().row();
  
  selected_id = selected;
  modifier_model = modifier_module->GetUnit(selected);
  ModelToForm();
  
  return;
}

void NewModifModuleDlg::removeObject() {
  int selected = widget.ObjectList->selectionModel()->currentIndex().row();
  
  modifier_module->RemoveUnit(selected);
  RefreshListView();
  return;
}

void NewModifModuleDlg::saveObject() {
  FormToModel();
  modifier_module->EditUnit(selected_id, modifier_model);
  RefreshListView();
  
  return;
}

void NewModifModuleDlg::FormToModel() {
  modifier_model.SetDeltaHP(widget.sbDeltaHP->value());
  modifier_model.SetPerHP(widget.sbDeltaHPper->value());
  modifier_model.SetDeltaST(widget.sbDeltaSt->value());
  modifier_model.SetPerST(widget.sbDeltaStper->value());
  
  modifier_model.SetClass((IModifier::E_MODIFIER)widget.cbClass->itemData(widget.cbClass->currentIndex()).toInt());
  modifier_model.SetDesc(widget.leDesc->text().toStdString());
  modifier_model.SetDuration(widget.sbDuration->value());
}

void NewModifModuleDlg::ModelToForm() {
  widget.sbDeltaHP->setValue(modifier_model.GetDeltaHP());
  widget.sbDeltaHPper->setValue(modifier_model.GetPerHP());
  widget.sbDeltaSt->setValue(modifier_model.GetDeltaST());
  widget.sbDeltaStper->setValue(modifier_model.GetPerST());
  
  widget.cbClass->setCurrentIndex(widget.cbClass->findData(QVariant((int)modifier_model.GetClass())));
  widget.leDesc->setText(QString(modifier_model.GetDesc().c_str()));
  widget.sbDuration->setValue(modifier_model.GetDuration());
}
