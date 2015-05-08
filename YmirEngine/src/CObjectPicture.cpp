/* 
 * File:   CObjectPicture.cpp
 * Author: Matej Pechac
 * 
 * Created on May 4, 2015, 9:27 PM
 */

#include <CMathUtils.h>

#include "CObjectPicture.h"

CObjectPicture::CObjectPicture(CSprite* asset, CObjectEntity* object_entity, double z_index) {
  this->asset = asset;
  this->object_entity = object_entity;
  this->z_index = z_index;
}

CObjectPicture::CObjectPicture(const CObjectPicture& orig) {
  object_entity = orig.object_entity;
  asset = orig.asset;
  z_index = orig.z_index;  
}

CObjectPicture::~CObjectPicture() {
}

void CObjectPicture::OnRender(SDL_Surface* dest, SDL_Rect camera)
{
  SDL_Rect      render_area;
  SDL_Surface*  surf = asset->GetSurface(object_entity->GetDirection(),0,0);
  
  render_area.x = camera.x * MAP_ELEM - surf->w;
  render_area.y = camera.y * MAP_ELEM - surf->h;
  render_area.w = camera.w * MAP_ELEM + 2 * surf->w;
  render_area.h = camera.h * MAP_ELEM + 2 * surf->h;
  
  SDL_Rect rect = {GetRenderX(), GetRenderY(), (Uint16)surf->w, (Uint16)surf->h};
  
  if (CMathUtils::intersect(rect, render_area))
  {
    rect.x = GetRenderX() - camera.x * MAP_ELEM;
    rect.y = GetRenderY() - camera.y * MAP_ELEM;
            
    SDL_BlitSurface(surf, NULL, dest, &rect);
  }
}

bool CObjectPicture::operator <(CObjectPicture& ent) {
  if (GetRenderY() == ent.GetRenderY()) {
    return (this->z_index < ent.z_index);
  }
  else {
    return (this->GetRenderY() < ent.GetRenderY());
  }
}

