/* 
 * File:   CObjectRender.cpp
 * Author: Matej Pechac
 * 
 * Created on May 30, 2014, 7:46 PM
 */

#include "CObjectRender.h"
#include "CObject.h"
#include "GlobalDefine.h"
#include <iostream>

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
  if (object_module == NULL) {
    return false;
  }
  
  for(int i = 0; i < object_module->GetSize(); i++) {
    CObject object = object_module->GetUnit(i);
    string path = object.GetImage();
    
    SDL_Surface *new_surf;   
    
    new_surf = IMG_Load(path.c_str());
    if (new_surf == NULL) {
      return false;
    }
    else {
      object_sprite[object.GetID()] = new CSprite(new_surf, &object);
    }    
  }
  
  return true;
}

void CObjectRender::OnRender(SDL_Surface* dest, CObjectEntity* object_entity, int x, int y) {
  CObject* object = object_entity->GetRootObject();
  SDL_Surface* surf = object_sprite[object->GetID()]->GetSurface(object_entity->GetDirection(),0,0);
  SDL_Rect rect = {(Sint16)x, (Sint16)y, (Uint16)surf->w, (Uint16)surf->h};
  SDL_BlitSurface(surf, NULL, dest, &rect);  
}



