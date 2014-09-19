/*
 * File:   NewObjectModuleDlg.cpp
 * Author: Matej Pechac
 *
 * Created on May 10, 2014, 2:33 PM
 */

#include "NewObjectModuleDlg.h"
#include "GlobalDefine.h"

#include <QFileDialog>
#include <qt4/QtGui/QMessageBox>
#include <qt4/Qt/qpainter.h>

NewObjectModuleDlg::NewObjectModuleDlg() {
  widget.setupUi(this);

  connect(widget.bAdd, SIGNAL(clicked()), this, SLOT(addObject()));
  connect(widget.bEdit, SIGNAL(clicked()), this, SLOT(editObject()));
  connect(widget.bDelete, SIGNAL(clicked()), this, SLOT(removeObject()));
  connect(widget.bSave, SIGNAL(clicked()), this, SLOT(saveObject()));
  
  connect(widget.bChooseFile, SIGNAL(clicked()), this, SLOT(chooseFile()));
  
  connect(widget.lImage, SIGNAL(clicked()), this, SLOT(imageOnclick()));

  connect(widget.sbXSize, SIGNAL(valueChanged(int)), this, SLOT(SizeXChanged(int)));
  connect(widget.sbYSize, SIGNAL(valueChanged(int)), this, SLOT(SizeYChanged(int)));

  connect(widget.cbClass, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeClass(int)));

  object_module = new CModule<CObject>();
  object_module->LoadFromXML("data/objects", "objects", "object");
  widget.leModuleName->setText(OBJECT_LIST);
  
  listview_model = new QStandardItemModel();
  
  object_image = NULL;
  
  RefreshListView();
  RefreshComboBox();
}

NewObjectModuleDlg::~NewObjectModuleDlg() {
}

void NewObjectModuleDlg::accept() {
  object_module->SaveToXML(string("objects"), string("object"));
  QDialog::accept();  
}

void NewObjectModuleDlg::RefreshListView() {
  listview_model->clear();
  
  for(int i = 0; i < object_module->GetSize(); i++) {
    QStandardItem *item = new QStandardItem(QString(object_module->GetUnit(i).GetDesc().c_str()));   
    listview_model->appendRow(item);
  }

  widget.ObjectList->setModel(listview_model);  
}

void NewObjectModuleDlg::RefreshComboBox() {
  widget.cbClass->clear();
        
  for(map<int, string>::iterator it = object_class.getClasses()->begin(); it != object_class.getClasses()->end(); it++) {
    pair<int, string> obj_class = *it;
    widget.cbClass->addItem(QString(obj_class.second.c_str()), QVariant(obj_class.first));
  }  

}

void NewObjectModuleDlg::RefreshImage(QString _filename) {
  QString filename(_filename);
  
  if (object_image != NULL) {
    delete object_image;
  }
  
  object_image = new QPixmap(filename);
  
  DrawImage();
}

void NewObjectModuleDlg::DrawImage() {
  DrawGrid(object_image);
  
  widget.lImage->setPixmap(*object_image);  
}

void NewObjectModuleDlg::DrawGrid(QPixmap* pixmap) {
  QPainter pixPaint(pixmap);
  
  int elem_x = pixmap->width() / MAP_ELEM;
  int elem_y = pixmap->height() / MAP_ELEM;
  
  for(int i = 0; i < elem_y; i++) {
    pixPaint.drawLine(0, i * MAP_ELEM,  pixmap->width(), i * MAP_ELEM);
  }
  
  for(int j = 0; j < elem_x; j++) {
    pixPaint.drawLine(j * MAP_ELEM, 0, j * MAP_ELEM, pixmap->height());
  }  
  
  int* block_map = object_model.GetBlockMap();
  
  pixPaint.setPen(QColor(255,255,255));
  
  for(int i = 0; i < elem_y; i++) {
    for(int j = 0; j < elem_x; j++) {
      if (block_map[i*elem_x+j] == 99) {
        pixPaint.drawLine(j * MAP_ELEM, i * MAP_ELEM, (j+1) * MAP_ELEM, (i+1) * MAP_ELEM);
      }
    }
  }
}

void NewObjectModuleDlg::addObject() {
  FormToModel();
  object_module->AddUnit(object_model);
  RefreshListView();
  
  return;
}

void NewObjectModuleDlg::editObject() {
  int selected = widget.ObjectList->selectionModel()->currentIndex().row();
  
  selected_id = selected;
  object_model = object_module->GetUnit(selected);
  ModelToForm();
  
  return;
}

void NewObjectModuleDlg::removeObject() {
  int selected = widget.ObjectList->selectionModel()->currentIndex().row();
  
  object_module->RemoveUnit(selected);
  RefreshListView();
  return;
}

void NewObjectModuleDlg::saveObject() {
  FormToModel();
  object_module->EditUnit(selected_id, object_model);
  RefreshListView();
  
  return;
}

void NewObjectModuleDlg::FormToModel() {
  object_model.SetImage(widget.leFilename->text().toStdString());
  object_model.SetDesc(widget.leDesc->text().toStdString());
  object_model.SetClass((CObject::E_CLASSES)widget.cbClass->itemData(widget.cbClass->currentIndex()).toInt());
}

void NewObjectModuleDlg::ModelToForm() {
  widget.leFilename->setText(QString(object_model.GetImage().c_str()));
  widget.leDesc->setText(QString(object_model.GetDesc().c_str()));
  widget.cbClass->setCurrentIndex(widget.cbClass->findData(object_model.GetClass()));
}

void NewObjectModuleDlg::chooseFile() {
  QString usersfilename = QFileDialog::getOpenFileName( this,
                                                        "Select source file",
                                                        ".",
                                                        "PNG files (*.png);; All files (*.*)");
    

  
  QStringList str_list = usersfilename.split("/");
  usersfilename = IMAGE_PATH_OBJECTS + str_list.last();
          
  widget.leFilename->setText(usersfilename);
  
  RefreshImage(usersfilename);  
}

void NewObjectModuleDlg::imageOnclick() {
  QPoint click = widget.lImage->GetMousePosition();
  
  int* block_map = object_model.GetBlockMap();
  
  int click_x = click.x() / MAP_ELEM;
  int click_y = click.y() / MAP_ELEM;
  
  if (block_map[click_y*object_model.GetXSize()+click_x] == 0) {
    block_map[click_y*object_model.GetXSize()+click_x] = 99;
  }
  else {
    block_map[click_y*object_model.GetXSize()+click_x] = 0;
  }
  
  DrawImage();  
}

void NewObjectModuleDlg::SizeXChanged(int val) {
  object_model.SetXSize(val);
}

void NewObjectModuleDlg::SizeYChanged(int val) {
  object_model.SetYSize(val);
}

void NewObjectModuleDlg::ChangeClass(int val) {
  switch((CObject::E_CLASSES)widget.cbClass->itemData(val).toInt()) {
    case CObject::TECH:
      break;
    case CObject::PROJECTILE:
      QMessageBox::warning(this, QString("Warning"), QString("Use projectile module editor to edit projectiles!"), 1, 0);
      widget.cbClass->setCurrentIndex(widget.cbClass->findData(CObject::TECH));      
      break;
    case CObject::UNIT:
      QMessageBox::warning(this, QString("Warning"), QString("Use unit module editor to edit units!"), 1, 0);
      widget.cbClass->setCurrentIndex(widget.cbClass->findData(CObject::TECH));
      break;
  }
}
