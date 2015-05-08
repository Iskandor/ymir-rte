/* 
 * File:   CUnitPicture.cpp
 * Author: matej
 * 
 * Created on May 4, 2015, 9:30 PM
 */

#include "CUnitPicture.h"
#include "CMathUtils.h"
#include <SDL_gfxPrimitives.h>


CUnitPicture::CUnitPicture(CSprite* asset, SDL_Surface* insignia_asset, SDL_Surface* insignia_bckg, CUnitEntity* unit_entity, double z_index) : CObjectPicture(asset, unit_entity, z_index) {
  this->insignia_asset = insignia_asset;
  this->insignia_bckg = insignia_bckg;
}

CUnitPicture::CUnitPicture(const CUnitPicture& orig) : CObjectPicture(orig) {
  this->insignia_asset = orig.insignia_asset;
  this->insignia_bckg = orig.insignia_bckg;
}

CUnitPicture::~CUnitPicture() {
}

void CUnitPicture::OnRender(SDL_Surface* dest, SDL_Rect camera)
{
  SDL_Surface*  surf = asset->GetSurface(object_entity->GetDirection(),0,0);
  SDL_Rect      render_area;
  
  render_area.x = camera.x * MAP_ELEM - surf->w;
  render_area.y = camera.y * MAP_ELEM - surf->h;
  render_area.w = camera.w * MAP_ELEM + 2 * surf->w;
  render_area.h = camera.h * MAP_ELEM + 2 * surf->h;
  
  SDL_Rect rect = {GetRenderX(), GetRenderY(), (Uint16)surf->w, (Uint16)surf->h};
  
  if (CMathUtils::intersect(rect, render_area))
  {
    Sint16 x = GetRenderX() - camera.x * MAP_ELEM;
    Sint16 y = GetRenderY() - camera.y * MAP_ELEM;
  
    double  hp_bar = (double)((CUnitEntity*)object_entity)->GetHP() / (double)((CUnitEntity*)object_entity)->GetMaxHP();
    Sint16  x1 = x + 1;
    Sint16  y1 = y + 1;
    Sint16  x2 = x + (Sint16)(hp_bar * MAP_ELEM-1);
    Sint16  y2 = y + 5;    


    SDL_Rect insignia_rect = {(Sint16)x, (Sint16)y + 8, MAP_ELEM, MAP_ELEM};
    SDL_BlitSurface(insignia_bckg, NULL, dest, &insignia_rect);

    SDL_BlitSurface(insignia_asset, NULL, dest, &insignia_rect);

    rectangleRGBA(dest, x, y, x+MAP_ELEM, y+6, 64, 64, 64, 255);
    switch(((CUnitEntity*)object_entity)->GetPlayerID()) {
      case 0:
        boxRGBA(dest, x1, y1, x2, y2, 0, 0, 128, 224);
        break;
      case 1:
        boxRGBA(dest, x1, y1, x2, y2, 128, 0, 0, 224 );
        break;
      case 2:
        boxRGBA(dest, x1, y1, x2, y2, 128, 128, 0, 224 );
        break;

    }

    CObjectPicture::OnRender(dest, camera);
  }
}

