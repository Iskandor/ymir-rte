/*
 * File:   NewMapDlg.cpp
 * Author: Matej Pechac
 *
 * Created on October 8, 2012, 7:05 PM
 */

#include "NewMapDlg.h"

NewMapDlg::NewMapDlg(CModule<CTile> *tile_module) {
  widget.setupUi(this);
  
  this->tile_module = tile_module;
  
  RefreshComboBox();
}

NewMapDlg::~NewMapDlg() {
}

void NewMapDlg::accept() {
  map_dlg.name = widget.leName->text().toUtf8().constData();
  map_dlg.x = widget.leMapX->text().toInt();
  map_dlg.y = widget.leMapY->text().toInt();
  map_dlg.centroids[0] = widget.leEarth->text().toInt();
  map_dlg.centroids[1] = widget.leWater->text().toInt();
  map_dlg.centroids[2] = widget.leAir->text().toInt();
  map_dlg.centroids[3] = widget.leFire->text().toInt();
  map_dlg.default_tile = widget.cbDefaultTile->itemData(widget.cbDefaultTile->currentIndex()).toInt();

  QDialog::accept();
}

void NewMapDlg::RefreshComboBox() {
  widget.cbDefaultTile->clear();
          
  for(int i = 0; i < tile_module->GetSize(); i++) {
    QString item = tile_module->GetUnit(i).getName().c_str();  
    widget.cbDefaultTile->addItem(item, QVariant(tile_module->GetUnit(i).GetID()));
  }  
}


