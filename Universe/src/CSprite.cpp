/* 
 * File:   CSprite.cpp
 * Author: Matej Pechac
 * 
 * Created on April 26, 2014, 6:39 PM
 */

#include "CSprite.h"
#include "GlobalDefine.h"

CSprite::CSprite(SDL_Surface* source, CUnit* unit) {
  SDL_Rect src_rect;
  
  surface_map = new SDL_Surface*[2];
  dir_indexer = new int[2];
  anim_indexer = new int[2];  
  
  src_rect.w = unit->GetXSize() * MAP_ELEM;
  src_rect.h = unit->GetYSize() * MAP_ELEM;
  
  for(int i = 0; i < 2; i++) {
    surface_map[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, src_rect.w, src_rect.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    dir_indexer[i] = i;
    anim_indexer[i] = 0;
    
    src_rect.x = 0;
    src_rect.y = src_rect.h * i;
    
    SDL_BlitSurface(source, &src_rect, surface_map[i], NULL);
    SDL_SetColorKey(surface_map[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surface_map[i]->format, 255, 0, 255));
    surface_map[i] = SDL_DisplayFormat(surface_map[i]);
  }
}

CSprite::CSprite(const CSprite& orig) {
}

CSprite::~CSprite() {
  for(int i = 0; i < 2; i++) {
    SDL_FreeSurface(surface_map[i]);
  }
  delete[] surface_map;
  
  delete[] dir_indexer;
  delete[] anim_indexer;
}

SDL_Surface* CSprite::GetSurface(int direction, int animation, int field) {
  if (surface_map != NULL) {
    return surface_map[dir_indexer[direction] + anim_indexer[animation] + field];
  }
  else {
    return NULL;
  }
}

