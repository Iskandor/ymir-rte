/* 
 * File:   CMapRender.h
 * Author: matej
 *
 * Created on February 6, 2013, 6:05 PM
 */

#ifndef CMAPRENDER_H
#define	CMAPRENDER_H

#include <SDL/SDL.h>
#include "CMap.h"

#include <Qt/qwidget.h>

class CMapRender {
public:
  CMapRender(QWidget* widget);
  CMapRender(const CMapRender& orig);
  virtual ~CMapRender();
  
  void onRender();
  void setMapPtr(CMap* _map);
  
  SDL_Rect* GetCamera();
  void      SetCameraX(int x);
  void      SetCameraY(int y);
private:
  CMap      *map;
  SDL_Rect  camera;
  
  QWidget*  drawing_widget;
  
  QColor decide_color(CTile* p_tile);
};

#endif	/* CMAPRENDER_H */

