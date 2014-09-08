/* 
 * File:   CTileRender.h
 * Author: Matej Pechac
 *
 * Created on October 31, 2013, 1:30 PM
 */

#ifndef CTILERENDER_H
#define	CTILERENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>

#include "CTile.h"
#include "CModule.h"

using namespace std;

class CTileRender {
public:
  CTileRender(CModule<CTile> *tile_module);
  CTileRender(const CTileRender& orig);
  virtual ~CTileRender();
  
public:
  bool LoadSurfaces();
  void OnRender(SDL_Surface* dest, CTile* tile, int x, int y);
  
private:
  CModule<CTile>          *tile_module;
  map<int, SDL_Surface*>  tile_surface;
};

#endif	/* CTILERENDER_H */

