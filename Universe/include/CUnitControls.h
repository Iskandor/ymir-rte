/* 
 * File:   CUnitControls.h
 * Author: Matej Pechac
 *
 * Created on April 12, 2014, 10:23 AM
 */

#ifndef CUNITCONTROLS_H
#define	CUNITCONTROLS_H

#include <SDL/SDL.h>

#include "CMap.h"
#include "CMapRender.h"

class CUnitControls {
public:
  CUnitControls(CMapRender* map_render);
  CUnitControls(const CUnitControls& orig);
  virtual ~CUnitControls();
  
  void OnEvent(SDL_Event* event);
  void OnLoop();
  
private:
  CMapRender*   map_render;
  CMap*         map;
  
  CUnitEntity*  selected_unit;
};

#endif	/* CUNITCONTROLS_H */

