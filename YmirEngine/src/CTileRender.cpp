/* 
 * File:   CTileRender.cpp
 * Author: Matej Pechac
 * 
 * Created on October 31, 2013, 1:30 PM
 */
#include <iostream>
#include "CTileRender.h"
#include "GlobalDefine.h"

CTileRender::CTileRender(CModule<CTile> *tile_module) {
  this->tile_module = tile_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading tile surfaces" << endl;
  }
}

CTileRender::CTileRender(const CTileRender& orig) {
  this->tile_module = orig.tile_module;
}

CTileRender::~CTileRender() {
}

bool CTileRender::LoadSurfaces() {
  if (tile_module == NULL) {
    return false;
  }
  
  for(int i = 0; i < tile_module->GetSize(); i++) {
    CTile tile = tile_module->GetUnit(i);
    string path = IMAGE_PATH_TILES + tile.getFilename();
    
    SDL_Surface *new_surf;   
    
    new_surf = IMG_Load(path.c_str());
    new_surf = SDL_DisplayFormat(new_surf);
    if (new_surf == NULL) {
      return false;
    }
    else {
      tile_surface[tile.GetID()] = new_surf;
    }
  }
  
  return true;
}
  
void CTileRender::OnRender(SDL_Surface* dest, CTile* tile, int x, int y) {
  SDL_Rect rect = {(Sint16)x, (Sint16)y, TILE_W, TILE_H};
  SDL_BlitSurface(tile_surface[tile->GetID()], NULL, dest, &rect);
}
