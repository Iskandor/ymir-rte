/* 
 * File:   CMapRender.h
 * Author: Matej Pechac
 *
 * Created on October 30, 2013, 9:15 PM
 */

#ifndef CMAPRENDER_H
#define	CMAPRENDER_H

#include <SDL/SDL.h>

#include "CMap.h"
#include "CMapSegment.h"
#include "CTileRender.h"
#include "CUnitRender.h"

using namespace std;

class CMapRender {
public:
  CMapRender(SDL_Rect* ,CMap* map, CTileRender* tile_render, CUnitRender* unit_render);
  CMapRender(const CMapRender& orig);
  virtual ~CMapRender();
  
public:
  void OnRender(SDL_Surface* dest);
  
  SDL_Rect*  GetCamera();
  SDL_Rect*  GetMainRect();
  CMap*      GetMap();
  
private:
  SDL_Rect      camera;
  
  SDL_Surface*  main_surf;
	SDL_Rect*     main_rect;
  
  CMap*           map;
  CTileRender*    tile_render;
  CUnitRender*    unit_render;
  
  vector<CMapSegment*>  map_segments;
};

#endif	/* CMAPRENDER_H */

