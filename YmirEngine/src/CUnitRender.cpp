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

CUnitRender::CUnitRender(CModule<CUnit> *unit_module) : IRender<CUnitPicture>() {
  this->unit_module = unit_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading unit surfaces" << endl;
  }  
}

CUnitRender::CUnitRender(const CUnitRender& orig) : IRender<CUnitPicture>(orig) {
  unit_module = orig.unit_module;
  insignia_bckg = orig.insignia_bckg;
  insignia = orig.insignia;  
}

CUnitRender::~CUnitRender() {
}

bool CUnitRender::LoadSurfaces() {
  SDL_Surface *new_surf = NULL;
  
  if (unit_module == NULL) {
    return false;
  }
  
  for(int i = 0; i < unit_module->GetSize(); i++) {
    CUnit unit = unit_module->GetUnit(i);
    string path = unit.GetImage();

    new_surf = IMG_Load(path.c_str());
    if (new_surf == NULL) {
      return false;
    }
    else {
      sprite_map[unit.GetID()] = new CSprite(new_surf, &unit);
    }    
  }
  
  string path = IMAGE_PATH_INSIGNIA;
  path.append("shield.png");
  
  new_surf = IMG_Load(path.c_str());

  if (new_surf == NULL) {
    return false;
  }  
  
  for(Sint16 i = 0; i < MAX_PLAYER; i++) {
    insignia_bckg[i] = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_RLEACCEL, MAP_ELEM, MAP_ELEM, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_SetColorKey(insignia_bckg[i], SDL_SRCCOLORKEY, SDL_MapRGB(insignia_bckg[i]->format, 255, 0, 255));
    SDL_SetAlpha(insignia_bckg[i], SDL_SRCALPHA, 224);
    insignia_bckg[i] = SDL_DisplayFormat(insignia_bckg[i]);
    
    SDL_Rect rect_src = {(Sint16)(i*MAP_ELEM), 0, MAP_ELEM, MAP_ELEM};
    if (SDL_BlitSurface(new_surf, &rect_src, insignia_bckg[i], NULL) != 0) {
      return false;
    }
  }

  path = IMAGE_PATH_INSIGNIA;
  path.append("insignia.png");
  
  new_surf = IMG_Load(path.c_str());

  if (new_surf == NULL) {
    return false;
  }
  
  for(int i = 0; i < unit_module->GetSize(); i++) {
    CUnit unit = unit_module->GetUnit(i);
    
    insignia[unit.GetID()] = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_RLEACCEL, MAP_ELEM, MAP_ELEM, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_SetColorKey(insignia[unit.GetID()], SDL_SRCCOLORKEY, SDL_MapRGB(insignia[unit.GetID()]->format, 255, 0, 255));
    SDL_SetAlpha(insignia[unit.GetID()], SDL_SRCALPHA, 96);
    insignia[unit.GetID()] = SDL_DisplayFormat(insignia[unit.GetID()]);
    
    SDL_Rect rect_src = {(Sint16)unit.getInsigniaPos().first, (Sint16)unit.getInsigniaPos().second, MAP_ELEM, MAP_ELEM};
    if (SDL_BlitSurface(new_surf, &rect_src, insignia[unit.GetID()], NULL) != 0) {
      return false;
    }    
  }  
  
  
  return true;
}

CUnitPicture* CUnitRender::addPicture(CObjectEntity* object_entity, double z_index)  {
    CUnitEntity* unit_entity = (CUnitEntity*)object_entity;
  
    CUnitPicture* picture = new CUnitPicture(sprite_map[unit_entity->GetRootObject()->GetID()], insignia[unit_entity->GetRootObject()->GetID()], insignia_bckg[unit_entity->GetPlayerID()], unit_entity, z_index);
    
    picture_buffer.emplace_back(picture);
    
    return picture;
}


