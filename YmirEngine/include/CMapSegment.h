/* 
 * File:   CMapSegment.h
 * Author: Matej Pechac
 *
 * Created on October 31, 2013, 12:13 PM
 */

#ifndef CMAPSEGMENT_H
#define	CMAPSEGMENT_H

#define X_DIM 1024
#define Y_DIM 1024

#include <SDL/SDL.h>

#include "CMap.h"
#include "CTileRender.h"
#include "CUnitRender.h"

class CMapSegment {
public:
  CMapSegment(int x, int y, CMap* map, CTileRender* tile_render);
  CMapSegment(const CMapSegment& orig);
  virtual ~CMapSegment();
  
public:
  void OnRender(SDL_Surface* dest, SDL_Rect* camera);
  
  int GetX();
  int GetY();
  
private:
  CMap*         map;
  CTileRender*  tile_render;
  int           x;
  int           y;
  
  SDL_Surface*  main_surf;
	SDL_Rect      main_rect;
  SDL_Rect      elem_rect;
  
};

#endif	/* CMAPSEGMENT_H */

