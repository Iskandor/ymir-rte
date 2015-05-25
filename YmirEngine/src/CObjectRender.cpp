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


CObjectRender::CObjectRender(CModule<CObject> *object_module) : IRender<CObjectPicture>() {
  this->object_module = object_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading object surfaces" << endl;
  }  
}

CObjectRender::CObjectRender(const CObjectRender& orig) : IRender<CObjectPicture>(orig) {
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
      sprite_map[object.GetID()] = new CSprite(new_surf, &object);
    }    
  }
  
  
  SDL_FreeSurface(new_surf);
  
  return true;
}



CObjectPicture* CObjectRender::addPicture(CObjectEntity* object_entity, double z_index)  {
    CObjectPicture* picture = new CObjectPicture(sprite_map[object_entity->GetRootObject()->GetID()], object_entity, z_index);
    
    picture_buffer.emplace_back(picture);
    
    return picture;
}



