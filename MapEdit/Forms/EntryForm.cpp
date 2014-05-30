/*
 * File:   EntryForm.cpp
 * Author: matej
 *
 * Created on October 8, 2012, 6:57 PM
 */
#include <QFileDialog>

#include "EntryForm.h"
#include "NewMapDlg.h"
#include "NewUnitModuleDlg.h"
#include "NewTileModuleDlg.h"
#include "NewObjectModuleDlg.h"

EntryForm::EntryForm() {
  widget.setupUi(this);

  connect(widget.actionNew_map, SIGNAL(triggered()), this, SLOT(newMap()));
  connect(widget.actionOpen_map, SIGNAL(triggered()), this, SLOT(openMap()));
  connect(widget.actionSave, SIGNAL(triggered()), this, SLOT(saveMap()));
  connect(widget.actionSave_as, SIGNAL(triggered()), this, SLOT(saveMapAs()));
  connect(widget.actionQuit, SIGNAL(triggered()), this, SLOT(exit()));
  connect(widget.actionUnit_Module, SIGNAL(triggered()), this, SLOT(openUnitModule()));
  connect(widget.actionTile_Module, SIGNAL(triggered()), this, SLOT(openTileModule()));
  connect(widget.actionObject_Modules, SIGNAL(triggered()), this, SLOT(openObjectModule()));

  connect(widget.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(moveCameraX(int)));
  connect(widget.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(moveCameraY(int)));

  map = NULL;
  map_render = new CMapRender(widget.drawingWidget);
  
  tile_module.LoadFromXML("data/tiles", "tiles", "tile");
  unit_module.LoadFromXML("data/default", "units", "unit");
}

EntryForm::~EntryForm() {
  if (map != NULL) {
    delete map;
  }
  
  delete map_render;
}

void EntryForm::newMap() {
  NewMapDlg dlg(&tile_module);

  if (dlg.exec()) {    
    map = new CMap(dlg.map_dlg.x, dlg.map_dlg.y, dlg.map_dlg.default_tile, &tile_module, &unit_module);
    map->setName(dlg.map_dlg.name);
    //map->generateMap(dlg.map_dlg.centroids[0], dlg.map_dlg.centroids[1], dlg.map_dlg.centroids[2], dlg.map_dlg.centroids[3]);
    map_render->setMapPtr(map);
    
    this->widget.horizontalScrollBar->setMaximum((dlg.map_dlg.x * TILE_PER_SEGMENT * ELEM_PER_TILE) - map_render->GetCamera()->w);
    this->widget.verticalScrollBar->setMaximum((dlg.map_dlg.y * TILE_PER_SEGMENT * ELEM_PER_TILE) - map_render->GetCamera()->h);
  }
}

void EntryForm::openMap() {
  QString usersfilename = QFileDialog::getOpenFileName( this,
                                                        "Open file",
                                                        ".",
                                                        "MAP files (*.map);; All files (*.*)");



  QStringList str_list = usersfilename.split("/");
  usersfilename = str_list.last();

  map->Load(usersfilename.toStdString());
}

void EntryForm::saveMap() {
}

void EntryForm::saveMapAs() {
  if (map != NULL) {
    QString usersfilename = QFileDialog::getSaveFileName( this,
                                                          "Save file as..",
                                                          ".",
                                                          "MAP files (*.map);; All files (*.*)");



    QStringList str_list = usersfilename.split("/");
    usersfilename = str_list.last();

    map->Save(usersfilename.toStdString());
  }
}

void EntryForm::exit() {
  this->close();
}

void EntryForm::openUnitModule() {
  NewUnitModuleDlg  dlg;
  
  if (dlg.exec()) {
    //tile_module.LoadFromXML("data/default", "units", "unit");
  }
}

void EntryForm::openTileModule() {
  NewTileModuleDlg  dlg;
  
  if (dlg.exec()) {
    tile_module.LoadFromXML("data/tiles", "tiles", "tile");
  }
}

void EntryForm::openObjectModule() {
  NewObjectModuleDlg  dlg;
  
  if (dlg.exec()) {
    //tile_module.LoadFromXML("data/tiles", "tiles", "tile");
  }
}

void EntryForm::paintEvent(QPaintEvent*) {
  if (map != NULL) {
    map_render->onRender();
  }
}

void EntryForm::repaint() {
  this->widget.drawingWidget->repaint();
}

void EntryForm::moveCameraX(int x) {
  map_render->SetCameraX(x);
  widget.drawingWidget->repaint();
}

void EntryForm::moveCameraY(int y) {
  map_render->SetCameraY(y);
  widget.drawingWidget->repaint();
}