/* 
 * File:   CObjectRender.cpp
 * Author: Matej Pechac
 * 
 * Created on May 30, 2014, 7:46 PM
 */

#include "CObjectRender.h"
#include "CObject.h"
#include "GlobalDefine.h"
#include "CUnitEntity.h"
#include <iostream>
#include <SDL_gfxPrimitives.h>

CObjectRender::CObjectRender(CModule<CObject> *object_module, CModule<CUnit> *unit_module) {
  this->object_module = object_module;
  this->unit_module = unit_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading object surfaces" << endl;
  }  
}

CObjectRender::CObjectRender(const CObjectRender& orig) {
  object_module = orig.object_module;
  unit_module = orig.unit_module;
  object_sprite = orig.object_sprite;
  insignia_bckg = orig.insignia_bckg;
  insignia = orig.insignia;
}

CObjectRender::~CObjectRender() {
}

bool CObjectRender::LoadSurfaces() {
  SDL_Surface *new_surf = NULL;
  
  if (object_module == NULL) {
    return false;
  }
  
  for(int i = 0; i < object_module->GetSize(); i++) {
    CObject object = object_module->GetUnit(i);
    string path = object.GetImage();
    
    new_surf = IMG_Load(path.c_str());
    if (new_surf == NULL) {
      return false;
    }
    else {
      object_sprite[object.GetID()] = new CSprite(new_surf, &object);
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
  
  SDL_FreeSurface(new_surf);
  
  return true;
}

void CObjectRender::OnRender(SDL_Surface* dest, CObjectEntity* object_entity, int x, int y) {
  CObject* object = object_entity->GetRootObject();
  SDL_Surface* surf = object_sprite[object->GetID()]->GetSurface(object_entity->GetDirection(),0,0);
   
  if (object_entity->GetClassName() == "unit_entity") {
    double  hp_bar = (double)((CUnitEntity*)object_entity)->GetHP() / (double)((CUnitEntity*)object_entity)->GetMaxHP();
    Sint16  x1 = x + 1;
    Sint16  y1 = y + 1;
    Sint16  x2 = x + (Sint16)(hp_bar * MAP_ELEM-1);
    Sint16  y2 = y + 5;    
    
    
    SDL_Rect insignia_rect = {(Sint16)x, (Sint16)y + 8, MAP_ELEM, MAP_ELEM};
    SDL_BlitSurface(insignia_bckg[((CUnitEntity*)object_entity)->GetPlayerID()], NULL, dest, &insignia_rect);

    SDL_BlitSurface(insignia[object_entity->GetRootObject()->GetID()], NULL, dest, &insignia_rect);
    
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
  }
  
  SDL_Rect rect = {(Sint16)x, (Sint16)y, (Uint16)surf->w, (Uint16)surf->h};
  SDL_BlitSurface(surf, NULL, dest, &rect);  
}



