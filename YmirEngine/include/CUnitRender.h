/* 
 * File:   CUnitRender.h
 * Author: matej
 *
 * Created on April 9, 2014, 7:09 PM
 */

#ifndef CUNITRENDER_H
#define	CUNITRENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>

#include "CUnitEntity.h"
#include "CModule.h"
#include "CSprite.h"

using namespace std;

class CUnitRender {
public:
  CUnitRender(CModule<CUnit> *unit_module);
  CUnitRender(const CUnitRender& orig);
  virtual ~CUnitRender();
  
public:
  bool LoadSurfaces();
  void OnRender(SDL_Surface* dest, CUnitEntity* unit_entity, int x, int y);
  
private:
  CModule<CUnit>          *unit_module;
  map<int, CSprite*>      unit_sprite;
  map<int, SDL_Surface*>  insignia_bckg;

};

#endif	/* CUNITRENDER_H */

