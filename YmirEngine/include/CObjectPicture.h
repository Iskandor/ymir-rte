/* 
 * File:   CObjectPicture.h
 * Author: Matej Pechac
 *
 * Created on May 4, 2015, 9:27 PM
 */

#ifndef COBJECTPICTURE_H
#define	COBJECTPICTURE_H

#include <SDL/SDL.h>
#include "GlobalDefine.h"
#include "CObjectEntity.h"
#include "CSprite.h"


class CObjectPicture {
public:
  CObjectPicture(CSprite* asset, CObjectEntity* object_entity, double z_index);
  CObjectPicture(const CObjectPicture& orig);
  virtual ~CObjectPicture();
  
protected:
  CObjectEntity*  object_entity;
  CSprite*        asset;

  double  z_index;
  
public:  
  virtual void OnRender(SDL_Surface* dest, SDL_Rect camera);
  
  Sint16 GetRenderX() { return object_entity->GetX() * MAP_ELEM; };
  Sint16 GetRenderY() { return object_entity->GetY() * MAP_ELEM; };
  
  void    SetZIndex(int z_index) { this->z_index = z_index; };
  double  GetZIndex() { return z_index; };
  
  CObjectEntity*  GetObjectEntity() { return object_entity; };
  
  bool operator< (CObjectPicture& picture);

};

#endif	/* COBJECTPICTURE_H */

