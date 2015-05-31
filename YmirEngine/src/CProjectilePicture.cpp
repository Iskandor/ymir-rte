/* 
 * File:   CProjectilePicture.cpp
 * Author: Matej Pechac
 * 
 * Created on May 4, 2015, 9:40 PM
 */

#include "CProjectilePicture.h"
#include "CMathUtils.h"

CProjectilePicture::CProjectilePicture(CSprite* asset, CProjectileEntity* projectile_entity, double z_index) : CPicture(asset, projectile_entity, z_index) {
}

CProjectilePicture::CProjectilePicture(const CProjectilePicture& orig) : CPicture(orig) {
}

CProjectilePicture::~CProjectilePicture() {
}

void CProjectilePicture::OnRender(SDL_Surface* dest, SDL_Rect camera)
{
  SDL_Rect      render_area;
  SDL_Surface*  surf = asset->GetSurface(object_entity->GetDirection(),0,0);
  
  render_area.x = camera.x * MAP_ELEM - surf->w;
  render_area.y = camera.y * MAP_ELEM - surf->h;
  render_area.w = camera.w * MAP_ELEM + 2 * surf->w;
  render_area.h = camera.h * MAP_ELEM + 2 * surf->h;
  
  Sint16 render_x = dynamic_cast<CProjectileEntity*>(object_entity)->GetX();
  Sint16 render_y = dynamic_cast<CProjectileEntity*>(object_entity)->GetY();
  
  SDL_Rect rect = {render_x, render_y, (Uint16)surf->w, (Uint16)surf->h};
  
  if (CMathUtils::intersect(rect, render_area))
  {
    rect.x = render_x - camera.x * MAP_ELEM;
    rect.y = render_y - camera.y * MAP_ELEM;
            
    SDL_BlitSurface(surf, NULL, dest, &rect);
  }
}
