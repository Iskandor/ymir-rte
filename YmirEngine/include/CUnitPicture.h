/* 
 * File:   CUnitPicture.h
 * Author: matej
 *
 * Created on May 4, 2015, 9:30 PM
 */

#ifndef CUNITPICTURE_H
#define	CUNITPICTURE_H

#include "CObjectPicture.h"
#include "CUnitEntity.h"

class CUnitPicture : public CObjectPicture {
  public:
    CUnitPicture(CSprite* asset, SDL_Surface* insignia_asset, SDL_Surface* insignia_bckg, CUnitEntity* unit_entity, double z_index);
    CUnitPicture(const CUnitPicture& orig);
    virtual ~CUnitPicture();
  private:
    SDL_Surface*    insignia_asset;
    SDL_Surface*    insignia_bckg;
  
  public:
    void OnRender(SDL_Surface* dest, SDL_Rect camera);
};

#endif	/* CUNITPICTURE_H */

