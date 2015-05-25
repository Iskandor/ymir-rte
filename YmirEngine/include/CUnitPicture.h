/* 
 * File:   CUnitPicture.h
 * Author: Matej Pechac
 *
 * Created on May 4, 2015, 9:30 PM
 */

#ifndef CUNITPICTURE_H
#define	CUNITPICTURE_H

#include "CPicture.h"
#include "CUnitEntity.h"

class CUnitPicture : public CPicture {
  public:
    CUnitPicture(CSprite* asset, SDL_Surface* insignia_asset, SDL_Surface* insignia_bckg, CUnitEntity* unit_entity, double z_index);
    CUnitPicture(const CUnitPicture& orig);
    virtual ~CUnitPicture();
  
  public:
    virtual void OnRender(SDL_Surface* dest, SDL_Rect camera);
    
  private:
    SDL_Surface*    insignia_asset;
    SDL_Surface*    insignia_bckg;
    
};

#endif	/* CUNITPICTURE_H */

