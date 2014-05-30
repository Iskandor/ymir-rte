/* 
 * File:   CMapControls.h
 * Author: Matej Pechac
 *
 * Created on April 8, 2014, 7:50 PM
 */

#ifndef CMAPCONTROLS_H
#define	CMAPCONTROLS_H

#include <SDL/SDL.h>
#include "CMapRender.h"

using namespace std;

class CMapControls {
public:
  CMapControls(CMapRender* map_render);
  CMapControls(const CMapControls& orig);
  virtual ~CMapControls();
  
  void OnEvent(SDL_Event* event);
  void OnLoop();
  
private:
  bool            scrolling;
  pair<int, int>  scroll_direction;
  CMapRender*     map_render;
};

#endif	/* CMAPCONTROLS_H */

