/* 
 * File:   CPicture.h
 * Author: Matej Pechac
 *
 * Created on May 4, 2015, 9:27 PM
 */

#ifndef CPICTURE_H
#define	CPICTURE_H

#include <SDL/SDL.h>
#include "GlobalDefine.h"
#include "CObjectEntity.h"
#include "CSprite.h"


class CPicture {
public:
  CPicture(CSprite* asset, CObjectEntity* object_entity, double z_index);
  CPicture(const CPicture& orig);
  virtual ~CPicture();
  
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
  
  bool operator< (CPicture& picture);

};

#endif	/* COBJECTPICTURE_H */

