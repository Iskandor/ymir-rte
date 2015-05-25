/* 
 * File:   CObjectPicture.h
 * Author: Matej Pechac
 *
 * Created on May 23, 2015, 11:17 AM
 */

#ifndef COBJECTPICTURE_H
#define	COBJECTPICTURE_H

#include "CPicture.h"
#include "CObjectEntity.h"

class CObjectPicture : public CPicture {
  public:
    CObjectPicture(CSprite* asset, CObjectEntity* object_entity, double z_index);
    CObjectPicture(const CObjectPicture& orig);
    virtual ~CObjectPicture();

    public:
      virtual void OnRender(SDL_Surface* dest, SDL_Rect camera);
};

#endif	/* COBJECTPICTURE_H */

