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

#include "CObjectPicture.h"
#include "CModule.h"
#include "CSprite.h"
#include "CUnit.h"
#include "CProjectile.h"

class CObjectRender {
public:
  CObjectRender(CModule<CObject> *object_module, CModule<CUnit> *unit_module, CModule<CProjectile> *projectile_module);
  CObjectRender(const CObjectRender& orig);
  virtual ~CObjectRender();

  bool LoadSurfaces();
  void OnRender(SDL_Surface* dest, CObjectEntity* object_entity, int x, int y);
  void SortObjects(CObjectPicture*);

  virtual CObjectPicture* addPicture(CObjectEntity* object_entity, double z_index);
  void              remPicture(int id);
  
  multimap<double, CObjectPicture*, less< double > >* GetYSortedTree() { return &ysorted_tree; };
  CObjectPicture* GetObjectPicture(int object_id);
  
protected:
  CModule<CObject>                  *object_module;
  CModule<CUnit>                    *unit_module;
  CModule<CProjectile>              *projectile_module;
  
  map<int, SDL_Surface*>            insignia_bckg;
  map<int, SDL_Surface*>            insignia;
  map<int, CSprite*>                object_sprite;
  
  multimap<double, CObjectPicture*, less< double > > ysorted_tree;
};

#endif	/* COBJECTRENDER_H */

