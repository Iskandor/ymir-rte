/*
 * File:   NewUnitModuleDlg.cpp
 * Author: Matej Pechac
 *
 * Created on June 30, 2013, 4:33 PM
 */

#include "NewUnitModuleDlg.h"
#include "GlobalDefine.h"

#include <QFileDialog>
#include <QtCore>
#include <qt4/Qt/qpainter.h>

NewUnitModuleDlg::NewUnitModuleDlg() {
  widget.setupUi(this);
  
  connect(widget.AddUMButton, SIGNAL(clicked()), this, SLOT(addUnit()));
  connect(widget.EditUMButton, SIGNAL(clicked()), this, SLOT(editUnit()));
  connect(widget.DeleteUMButton, SIGNAL(clicked()), this, SLOT(removeUnit()));
  connect(widget.SaveBtn, SIGNAL(clicked()), this, SLOT(saveUnit()));
  
  connect(widget.ChooseBtn, SIGNAL(clicked()), this, SLOT(chooseFile()));
  
  connect(widget.ImageLb, SIGNAL(clicked()), this, SLOT(imageOnclick()));
  
  connect(widget.SizeXSb, SIGNAL(valueChanged(int)), this, SLOT(SizeXChanged(int)));
  connect(widget.SizeYSb, SIGNAL(valueChanged(int)), this, SLOT(SizeYChanged(int)));
  
  unit_module = new CModule<CUnit>();
  unit_module->LoadFromXML("data/units", "units", "unit");
  widget.UMLineEdit->setText(UNIT_LIST);
  
  race_list = new CRace("data/races");
  
  listview_model = new QStandardItemModel();
  
  unit_image = NULL;
  
  RefreshListView();
  RefreshComboBox();
}

NewUnitModuleDlg::~NewUnitModuleDlg() {
  delete listview_model;
}

void NewUnitModuleDlg::RefreshListView() {
  listview_model->clear();
  
  for(int i = 0; i < unit_module->GetSize(); i++) {
    QStandardItem *item = new QStandardItem(QString(unit_module->GetUnit(i).getClass().c_str()));   
    listview_model->appendRow(item);
  }

  widget.UnitListView->setModel(listview_model);  
}

void NewUnitModuleDlg::RefreshComboBox() {
  widget.RaceCbx->clear();
          
  for(int i = 0; i < race_list->getSize(); i++) {
    QString item = race_list->getNames()[i].c_str();   
    widget.RaceCbx->addItem(item);
  }  
}

void NewUnitModuleDlg::RefreshImage(QString _filename) {
  QString filename(IMAGE_PATH_UNITS);
  filename.append(_filename);
  
  if (unit_image != NULL) {
    delete unit_image;
  }
  
  unit_image = new QPixmap(filename);
  
  DrawImage();
}

void NewUnitModuleDlg::DrawImage() {
  DrawGrid(unit_image);
  
  widget.ImageLb->setPixmap(*unit_image);  
}

void NewUnitModuleDlg::addUnit() {
  FormToModel();
  unit_module->AddUnit(unit_model);
  RefreshListView();
  
  return;
}

void NewUnitModuleDlg::editUnit() {
  int selected = widget.UnitListView->selectionModel()->currentIndex().row();
  
  selected_id = selected;
  unit_model = unit_module->GetUnit(selected);
  ModelToForm();
  
  return;
}

void NewUnitModuleDlg::removeUnit() {
  int selected = widget.UnitListView->selectionModel()->currentIndex().row();
  
  unit_module->RemoveUnit(selected);
  RefreshListView();
  return;
}

void NewUnitModuleDlg::saveUnit() {
  FormToModel();
  unit_module->EditUnit(selected_id, unit_model);
  RefreshListView();
  
  return;
}

void NewUnitModuleDlg::chooseFile() {
  QString usersfilename = QFileDialog::getOpenFileName( this,
                                                        "Select source file",
                                                        ".",
                                                        "PNG files (*.png);; All files (*.*)");
    

  
  QStringList str_list = usersfilename.split("/");
  usersfilename = str_list.last();
          
  widget.ImageLed->setText(usersfilename);
  
  RefreshImage(usersfilename);
}

void NewUnitModuleDlg::imageOnclick() {
  QPoint click = widget.ImageLb->GetMousePosition();
  
  int* block_map = unit_model.GetBlockMap();
  
  int click_x = click.x() / MAP_ELEM;
  int click_y = click.y() / MAP_ELEM;
  
  if (block_map[click_y*unit_model.GetXSize()+click_x] == 0) {
    block_map[click_y*unit_model.GetXSize()+click_x] = 99;
  }
  else {
    block_map[click_y*unit_model.GetXSize()+click_x] = 0;
  }
  
  DrawImage();
}

void NewUnitModuleDlg::accept() {
  
  unit_module->SaveToXML(string("units"), string("unit"));
  
  QDialog::accept();
}

void NewUnitModuleDlg::FormToModel() {
  vector<int>     prop(N_PROP);
  vector<int>     elem(N_ELEM);
  vector<double>  att(N_ATTACK);
  vector<double>  def(N_ATTACK);
  
  unit_model.setClass(widget.NameLed->text().toStdString());
  unit_model.setRace(widget.RaceCbx->currentText().toStdString());
  unit_model.SetImage(widget.ImageLed->text().toStdString());
  
  prop[STR_IND] = widget.StrSbx->value();
  prop[END_IND] = widget.EndSbx->value();
  prop[AGL_IND] = widget.AglSbx->value();
  prop[INT_IND] = widget.IntSbx->value();
  prop[DIV_IND] = widget.DivSbx->value();
  prop[CHA_IND] = widget.ChrSbx->value();
  
  unit_model.setProp(prop);
  unit_model.setSight(widget.SightSbx->value());
  unit_model.setAttackRange(widget.AttRngSbx->value());
  unit_model.setDamageArea(widget.DamSbx->value());
  
  elem[EAR_IND] = widget.EarthSbx->value();
  elem[WAT_IND] = widget.WaterSbx->value();
  elem[AIR_IND] = widget.AirSbx->value();
  elem[FIR_IND] = widget.FireSbx->value();
  
  unit_model.setElem(elem);
  
  att[BLUNT_IND] = (double)widget.BluntASbx->value() / 100;
  att[SLASH_IND] = (double)widget.SlashASbx->value() / 100;
  att[STAB_IND]  = (double)widget.StabASbx->value() / 100;
  
  unit_model.setAVP(att);
  
  def[BLUNT_IND] = (double)widget.BluntDSbx->value() / 100;
  def[SLASH_IND] = (double)widget.SlashDSbx->value() / 100;
  def[STAB_IND]  = (double)widget.StabDSbx->value() / 100;
  
  unit_model.setRVP(def);
  
  unit_model.SetXSize(widget.SizeXSb->value());
  unit_model.SetYSize(widget.SizeYSb->value());
}

void NewUnitModuleDlg::ModelToForm() {
  
  widget.NameLed->setText(QString(unit_model.getClass().c_str()));
  widget.RaceCbx->setCurrentIndex(race_list->findName(unit_model.getRace()));
  widget.ImageLed->setText(QString(unit_model.GetImage().c_str()));
  RefreshImage(QString(unit_model.GetImage().c_str()));
  
  widget.StrSbx->setValue(unit_model.getProp()[STR_IND]);
  widget.EndSbx->setValue(unit_model.getProp()[END_IND]);
  widget.AglSbx->setValue(unit_model.getProp()[AGL_IND]);
  widget.IntSbx->setValue(unit_model.getProp()[INT_IND]);
  widget.DivSbx->setValue(unit_model.getProp()[DIV_IND]);
  widget.ChrSbx->setValue(unit_model.getProp()[CHA_IND]);

  widget.SightSbx->setValue(unit_model.getSight());
  widget.AttRngSbx->setValue(unit_model.getAttackRange());
  widget.DamSbx->setValue(unit_model.getDamageArea());
  
  widget.EarthSbx->setValue(unit_model.getElem()[EAR_IND]);
  widget.WaterSbx->setValue(unit_model.getElem()[WAT_IND]);
  widget.AirSbx->setValue(unit_model.getElem()[AIR_IND]);
  widget.FireSbx->setValue(unit_model.getElem()[FIR_IND]);
  
  widget.BluntASbx->setValue((int)(unit_model.getAVP()[BLUNT_IND]*100));
  widget.SlashASbx->setValue((int)(unit_model.getAVP()[SLASH_IND]*100));
  widget.StabASbx->setValue((int)(unit_model.getAVP()[STAB_IND]*100));
  
  widget.BluntDSbx->setValue((int)(unit_model.getRVP()[BLUNT_IND]*100));
  widget.SlashDSbx->setValue((int)(unit_model.getRVP()[SLASH_IND]*100));
  widget.StabDSbx->setValue((int)(unit_model.getRVP()[STAB_IND]*100));
 
  widget.SizeXSb->setValue(unit_model.GetXSize());
  widget.SizeYSb->setValue(unit_model.GetYSize());
}

void NewUnitModuleDlg::DrawGrid(QPixmap* pixmap) {
  QPainter pixPaint(pixmap);
  
  int elem_x = pixmap->width() / MAP_ELEM;
  int elem_y = pixmap->height() / MAP_ELEM;
  
  for(int i = 0; i < elem_y; i++) {
    pixPaint.drawLine(0, i * MAP_ELEM,  pixmap->width(), i * MAP_ELEM);
  }
  
  for(int j = 0; j < elem_x; j++) {
    pixPaint.drawLine(j * MAP_ELEM, 0, j * MAP_ELEM, pixmap->height());
  }  
  
  int* block_map = unit_model.GetBlockMap();
  
  pixPaint.setPen(QColor(255,255,255));
  
  for(int i = 0; i < elem_y; i++) {
    for(int j = 0; j < elem_x; j++) {
      if (block_map[i*elem_x+j] == 99) {
        pixPaint.drawLine(j * MAP_ELEM, i * MAP_ELEM, (j+1) * MAP_ELEM, (i+1) * MAP_ELEM);
      }
    }
  }
}

void NewUnitModuleDlg::SizeXChanged(int val) {
  unit_model.SetXSize(val);
}

void NewUnitModuleDlg::SizeYChanged(int val) {
  unit_model.SetYSize(val);
}
