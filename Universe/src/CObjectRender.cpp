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

CObjectRender::CObjectRender(CModule<CObject> *object_module) {
  this->object_module = object_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading object surfaces" << endl;
  }  
}

CObjectRender::CObjectRender(const CObjectRender& orig) {
  object_module = orig.object_module;
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
          
  SDL_FreeSurface(new_surf);
  
  return true;
}

void CObjectRender::OnRender(SDL_Surface* dest, CObjectEntity* object_entity, int x, int y) {
  CObject* object = object_entity->GetRootObject();
  SDL_Surface* surf = object_sprite[object->GetID()]->GetSurface(object_entity->GetDirection(),0,0);
   
  if (object_entity->GetClassName() == "unit_entity") {
    double hp_bar = ((CUnitEntity*)object_entity)->GetHP() / ((CUnitEntity*)object_entity)->GetMaxHP();
    SDL_Rect insignia_rect = {0, 8, MAP_ELEM, MAP_ELEM};
    SDL_BlitSurface(insignia_bckg[((CUnitEntity*)object_entity)->GetPlayerID()], NULL, surf, &insignia_rect);
    
    rectangleRGBA(surf, 0, 0, MAP_ELEM, 6, 64, 64, 64, 255);
    switch(((CUnitEntity*)object_entity)->GetPlayerID()) {
      case 0:
        boxRGBA(surf, 1, 1, (Sint16)(hp_bar * MAP_ELEM-1), 5, 0, 0, 128, 224);
        break;
      case 1:
        boxRGBA(surf, 1, 1, (Sint16)(hp_bar * MAP_ELEM-1), 5, 128, 0, 0, 224 );
        break;
      case 2:
        boxRGBA(surf, 1, 1, (Sint16)(hp_bar * MAP_ELEM-1), 5, 128, 128, 0, 224 );
        break;
      
    }
  }
  
  SDL_Rect rect = {(Sint16)x, (Sint16)y, (Uint16)surf->w, (Uint16)surf->h};
  SDL_BlitSurface(surf, NULL, dest, &rect);  
}



