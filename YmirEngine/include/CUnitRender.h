/* 
 * File:   CUnitRender.h
 * Author: Matej Pechac
 *
 * Created on April 9, 2014, 7:09 PM
 */

#ifndef CUNITRENDER_H
#define	CUNITRENDER_H

#include <SDL/SDL_image.h>
#include <map>

#include "CUnit.h"
#include "CModule.h"
#include "IRender.h"
#include "CUnitPicture.h"


class CUnitRender : public IRender<CUnitPicture> {
public:
  CUnitRender(CModule<CUnit> *unit_module);
  CUnitRender(const CUnitRender& orig);
  virtual ~CUnitRender();
  
public:
  virtual bool LoadSurfaces();
  virtual CUnitPicture* addPicture(CObjectEntity* object_entity, double z_index);
  
private:
  CModule<CUnit>          *unit_module;
  map<int, SDL_Surface*>  insignia_bckg;
  map<int, SDL_Surface*>  insignia;

};

#endif	/* CUNITRENDER_H */

