/* 
 * File:   CSprite.h
 * Author: Matej Pechac
 *
 * Created on April 26, 2014, 6:39 PM
 */

#ifndef CSPRITE_H
#define	CSPRITE_H

#include <SDL/SDL.h>
#include "CObject.h"

class CSprite {
public:
  CSprite(SDL_Surface* source, CObject* unit);
  CSprite(const CSprite& orig);
  virtual ~CSprite();
  
  SDL_Surface*  GetSurface(int direction, int animation, int field);
  
private:
  SDL_Surface** surface_map;
  int*          anim_indexer;
  int           anim_size;
  int*          dir_indexer;
  int           dir_size;
};

#endif	/* CSPRITE_H */

