/*
 * File:   NewTileModuleDlg.cpp
 * Author: matej
 *
 * Created on October 31, 2013, 5:47 PM
 */

#include "NewTileModuleDlg.h"
#include "GlobalDefine.h"

#include <QFileDialog>
#include <QPixmap>
#include <QtCore>

NewTileModuleDlg::NewTileModuleDlg() {
  widget.setupUi(this);
  
  connect(widget.AddTMButton, SIGNAL(clicked()), this, SLOT(addTile()));
  connect(widget.EditTMButton, SIGNAL(clicked()), this, SLOT(editTile()));
  connect(widget.DeleteTMButton, SIGNAL(clicked()), this, SLOT(removeTile()));
  connect(widget.SaveTMButton, SIGNAL(clicked()), this, SLOT(saveTile()));
  
  connect(widget.ChooseTMButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
  
  tile_module = new CModule<CTile>();
  tile_module->LoadFromXML("data/tiles", "tiles", "tile");
  widget.TMLe->setText(TILE_LIST);
  
  listview_model = new QStandardItemModel();
  
  RefreshListView();
}

NewTileModuleDlg::~NewTileModuleDlg() {
  delete listview_model;
  delete tile_module;
}

void NewTileModuleDlg::addTile() {
  FormToModel();
  tile_module->AddUnit(tile_model);
  RefreshListView();  
}

void NewTileModuleDlg::editTile() {
  int selected = widget.TileListView->selectionModel()->currentIndex().row();
  
  selected_id = selected;
  tile_model = tile_module->GetUnit(selected);
  ModelToForm();  
}

void NewTileModuleDlg::removeTile() {
  int selected = widget.TileListView->selectionModel()->currentIndex().row();
  
  tile_module->RemoveUnit(selected);
  RefreshListView();  
}

void NewTileModuleDlg::saveTile() {
  FormToModel();
  tile_module->EditUnit(selected_id, tile_model);
  RefreshListView();  
}

void NewTileModuleDlg::accept() {
  tile_module->SaveToXML(string("tiles"), string("tile"));
  
  QDialog::accept();  
}

void NewTileModuleDlg::chooseFile() {
  QString usersfilename = QFileDialog::getOpenFileName( this,
                                                        "Select source file",
                                                        ".",
                                                        "PNG files (*.png);; All files (*.*)");
    

  
  QStringList str_list = usersfilename.split("/");
  usersfilename = str_list.last();
          
  widget.FileLe->setText(usersfilename);
  
  RefreshImage(usersfilename);  
}

void NewTileModuleDlg::RefreshImage(QString _filename){
  QString filename(IMAGE_PATH_TILES);
  filename.append(_filename);
  QPixmap mypix(filename);
  widget.ImageLb->setPixmap(mypix);
}

void NewTileModuleDlg::RefreshListView() {
  listview_model->clear();
  
  for(int i = 0; i < tile_module->GetSize(); i++) {
    QStandardItem *item = new QStandardItem(QString(tile_module->GetUnit(i).getName().c_str()));   
    listview_model->appendRow(item);
  }

  widget.TileListView->setModel(listview_model);   
}

void NewTileModuleDlg::ModelToForm() {
  widget.NameLe->setText(QString(tile_model.getName().c_str()));
  widget.FileLe->setText(QString(tile_model.getFilename().c_str()));
}

void NewTileModuleDlg::FormToModel() {
  tile_model.setName(widget.NameLe->text().toStdString());
  tile_model.setFilename(widget.FileLe->text().toStdString());
}