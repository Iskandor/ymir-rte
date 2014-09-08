/* 
 * File:   CObjectRender.h
 * Author: Matej Pechac
 *
 * Created on May 30, 2014, 7:46 PM
 */

#ifndef COBJECTRENDER_H
#define	COBJECTRENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>

#include "CObjectEntity.h"
#include "CModule.h"
#include "CSprite.h"
#include "CUnit.h"

class CObjectRender {
public:
  CObjectRender(CModule<CObject> *object_module, CModule<CUnit> *unit_module);
  CObjectRender(const CObjectRender& orig);
  virtual ~CObjectRender();

  bool LoadSurfaces();
  void OnRender(SDL_Surface* dest, CObjectEntity* object_entity, int x, int y);
  
private:
  CModule<CObject>                  *object_module;
  CModule<CUnit>                    *unit_module;
  map<int, CSprite*>                object_sprite;
  map<int, SDL_Surface*>            insignia_bckg;
  map<int, SDL_Surface*>            insignia;
};

#endif	/* COBJECTRENDER_H */

