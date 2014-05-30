/* 
 * File:   CMapRender.cpp
 * Author: Matej Pechac
 * 
 * Created on February 6, 2013, 6:05 PM
 */

#include "CMapRender.h"
#include "GlobalDefine.h"

#include <Qt/qpainter.h>
#include <Qt/qcolor.h>

CMapRender::CMapRender(QWidget* widget) {
  map = NULL;
  drawing_widget = widget;
  
  camera.x = 0;
  camera.y = 0;
  camera.w = drawing_widget->size().width() / TILE_W;
  camera.h = drawing_widget->size().height() / TILE_H;
  
}

CMapRender::CMapRender(const CMapRender& orig) {
  map = orig.map;
  drawing_widget = orig.drawing_widget;
  camera = orig.camera;
}

CMapRender::~CMapRender() {
}

void CMapRender::setMapPtr(CMap* _map) {
  map = _map;
}

void CMapRender::onRender() {
  CTile**  tile = map->getTilePtr();
  QPainter  painter(drawing_widget);
  int ci, cj;

  for(int i = 0; i < camera.h; i++) {
    for(int j = 0; j < camera.w; j++) {
      ci = i+camera.y;
      cj = j+camera.x;
      painter.setBrush(decide_color(tile[ci*map->getMapSizeY(sizemode_tile)+cj]));
      painter.drawRect(j * TILE_W, i * TILE_H, TILE_W, TILE_H);
    }
  }
}

QColor CMapRender::decide_color(CTile* p_tile) {
  int r = 0; //(p_tile->earth * 128 + p_tile->fire * 256 + p_tile->air * 256) / 3;
  int g = 0; //(p_tile->earth * 128 + p_tile->air * 256) / 2;
  int b = 0; //(p_tile->water * 256 + p_tile->air * 256) / 2;

  return QColor(r,g,b);
}

SDL_Rect* CMapRender::GetCamera() {
  return &camera;
}

void CMapRender::SetCameraX(int x) {
  camera.x = x;
}

void CMapRender::SetCameraY(int y) {
  camera.y = y;
}

