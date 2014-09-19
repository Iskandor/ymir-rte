/* 
 * File:   NewProjModuleDlh.cpp
 * Author: Matej Pechac
 * 
 * Created on September 17, 2014, 8:45 PM
 */

#include "NewProjModuleDlg.h"
#include "GlobalDefine.h"

#include <QFileDialog>
#include <qt4/QtGui/QMessageBox>
#include <qt4/Qt/qpainter.h>

NewProjModuleDlg::NewProjModuleDlg() {
  widget.setupUi(this);

  connect(widget.bAdd, SIGNAL(clicked()), this, SLOT(addObject()));
  connect(widget.bEdit, SIGNAL(clicked()), this, SLOT(editObject()));
  connect(widget.bDelete, SIGNAL(clicked()), this, SLOT(removeObject()));
  connect(widget.bSave, SIGNAL(clicked()), this, SLOT(saveObject()));
  
  connect(widget.bChooseFile, SIGNAL(clicked()), this, SLOT(chooseFile()));
  
  connect(widget.lImage, SIGNAL(clicked()), this, SLOT(imageOnclick()));

  connect(widget.sbXSize, SIGNAL(valueChanged(int)), this, SLOT(SizeXChanged(int)));
  connect(widget.sbYSize, SIGNAL(valueChanged(int)), this, SLOT(SizeYChanged(int)));

  projectile_module = new CModule<CProjectile>();
  projectile_module->LoadFromXML("data/projectiles", "projectiles", "projectile");
  widget.leModuleName->setText(PROJECTILES_LIST);
  
  listview_model = new QStandardItemModel();
  
  projectile_image = NULL;
  
  RefreshListView();
}

NewProjModuleDlg::~NewProjModuleDlg() {
}

void NewProjModuleDlg::accept() {
  projectile_module->SaveToXML(string("projectiles"), string("projectile"));
  QDialog::accept();  
}

void NewProjModuleDlg::RefreshListView() {
  listview_model->clear();
  
  for(int i = 0; i < projectile_module->GetSize(); i++) {
    QStandardItem *item = new QStandardItem(QString(projectile_module->GetUnit(i).GetDesc().c_str()));   
    listview_model->appendRow(item);
  }

  widget.ProjListView->setModel(listview_model);  
}

void NewProjModuleDlg::RefreshImage(QString _filename) {
  QString filename(_filename);
  
  if (projectile_image != NULL) {
    delete projectile_image;
  }
  
  projectile_image = new QPixmap(filename);
  
  DrawImage();
}

void NewProjModuleDlg::DrawImage() {
  DrawGrid(projectile_image);
  
  widget.lImage->setPixmap(*projectile_image);  
}

void NewProjModuleDlg::DrawGrid(QPixmap* pixmap) {
  QPainter pixPaint(pixmap);
  
  int elem_x = pixmap->width() / MAP_ELEM;
  int elem_y = pixmap->height() / MAP_ELEM;
  
  for(int i = 0; i < elem_y; i++) {
    pixPaint.drawLine(0, i * MAP_ELEM,  pixmap->width(), i * MAP_ELEM);
  }
  
  for(int j = 0; j < elem_x; j++) {
    pixPaint.drawLine(j * MAP_ELEM, 0, j * MAP_ELEM, pixmap->height());
  }  
  
  int* block_map = projectile_model.GetBlockMap();
  
  pixPaint.setPen(QColor(255,255,255));
  
  for(int i = 0; i < elem_y; i++) {
    for(int j = 0; j < elem_x; j++) {
      if (block_map[i*elem_x+j] == 99) {
        pixPaint.drawLine(j * MAP_ELEM, i * MAP_ELEM, (j+1) * MAP_ELEM, (i+1) * MAP_ELEM);
      }
    }
  }
}

void NewProjModuleDlg::addObject() {
  FormToModel();
  projectile_module->AddUnit(projectile_model);
  RefreshListView();
  
  return;
}

void NewProjModuleDlg::editObject() {
  int selected = widget.ProjListView->selectionModel()->currentIndex().row();
  
  selected_id = selected;
  projectile_model = projectile_module->GetUnit(selected);
  ModelToForm();
  
  return;
}

void NewProjModuleDlg::removeObject() {
  int selected = widget.ProjListView->selectionModel()->currentIndex().row();
  
  projectile_module->RemoveUnit(selected);
  RefreshListView();
  return;
}

void NewProjModuleDlg::saveObject() {
  FormToModel();
  projectile_module->EditUnit(selected_id, projectile_model);
  RefreshListView();
  
  return;
}

void NewProjModuleDlg::FormToModel() {
  projectile_model.SetImage(widget.leFilename->text().toStdString());
  projectile_model.SetDesc(widget.leDesc->text().toStdString());
  projectile_model.SetSpeed(widget.sbSpeed->value());
  projectile_model.SetClass(CObject::PROJECTILE);
}

void NewProjModuleDlg::ModelToForm() {
  widget.leFilename->setText(QString(projectile_model.GetImage().c_str()));
  widget.leDesc->setText(QString(projectile_model.GetDesc().c_str()));
  widget.sbSpeed->setValue(projectile_model.GetSpeed());
}

void NewProjModuleDlg::chooseFile() {
  QString usersfilename = QFileDialog::getOpenFileName( this,
                                                        "Select source file",
                                                        ".",
                                                        "PNG files (*.png);; All files (*.*)");
    

  
  QStringList str_list = usersfilename.split("/");
  usersfilename = IMAGE_PATH_PROJECTILES + str_list.last();
          
  widget.leFilename->setText(usersfilename);
  
  RefreshImage(usersfilename);  
}

void NewProjModuleDlg::imageOnclick() {
  QPoint click = widget.lImage->GetMousePosition();
  
  int* block_map = projectile_model.GetBlockMap();
  
  int click_x = click.x() / MAP_ELEM;
  int click_y = click.y() / MAP_ELEM;
  
  if (block_map[click_y*projectile_model.GetXSize()+click_x] == 0) {
    block_map[click_y*projectile_model.GetXSize()+click_x] = 99;
  }
  else {
    block_map[click_y*projectile_model.GetXSize()+click_x] = 0;
  }
  
  DrawImage();  
}

void NewProjModuleDlg::SizeXChanged(int val) {
  projectile_model.SetXSize(val);
}

void NewProjModuleDlg::SizeYChanged(int val) {
  projectile_model.SetYSize(val);
}

