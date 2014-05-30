/* 
 * File:   CUnitRender.cpp
 * Author: Matej Pechac
 * 
 * Created on April 9, 2014, 7:09 PM
 */

#include "CUnitRender.h"
#include "CUnit.h"
#include "GlobalDefine.h"
#include <iostream>

CUnitRender::CUnitRender(CModule<CUnit> *unit_module) {
  this->unit_module = unit_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading unit surfaces" << endl;
  }  
}

CUnitRender::CUnitRender(const CUnitRender& orig) {
  unit_module = orig.unit_module;
}

CUnitRender::~CUnitRender() {
}

bool CUnitRender::LoadSurfaces() {
  if (unit_module == NULL) {
    return false;
  }
  
  for(int i = 0; i < unit_module->GetSize(); i++) {
    CUnit unit = unit_module->GetUnit(i);
    string path = IMAGE_PATH_UNITS + unit.GetImage();
    
    SDL_Surface *new_surf;   
    
    new_surf = IMG_Load(path.c_str());
    if (new_surf == NULL) {
      return false;
    }
    else {
      //unit_surface[unit.getID()] = new_surf;
      unit_sprite[unit.GetID()] = new CSprite(new_surf, &unit);
    }    
  }
  
  return true;
}

void CUnitRender::OnRender(SDL_Surface* dest, CUnitEntity* unit_entity, int x, int y) {
  CUnit* unit = unit_entity->GetRootUnit();
  SDL_Surface* surf = unit_sprite[unit->GetID()]->GetSurface(unit_entity->GetDirection(),0,0);
  SDL_Rect rect = {x, y, surf->w, surf->h};
  SDL_BlitSurface(surf, NULL, dest, &rect);  
}

