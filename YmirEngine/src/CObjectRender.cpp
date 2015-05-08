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


CObjectRender::CObjectRender(CModule<CObject> *object_module, CModule<CUnit> *unit_module, CModule<CProjectile> *projectile_module) {
  this->object_module = object_module;
  this->unit_module = unit_module;
  this->projectile_module = projectile_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading object surfaces" << endl;
  }  
}

CObjectRender::CObjectRender(const CObjectRender& orig) {
  object_module = orig.object_module;
  unit_module = orig.unit_module;
  projectile_module = orig.projectile_module;
  object_sprite = orig.object_sprite;
  insignia_bckg = orig.insignia_bckg;
  insignia = orig.insignia;
  ysorted_tree = orig.ysorted_tree;
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
  
  if (projectile_module == NULL) {
    return false;
  }
  
  return true;
}

void CObjectRender::SortObjects(CObjectPicture* object_picture) {
  multimap<double, CObjectPicture*, less< double > >::iterator it;
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetObjectEntity()->GetID() == object_picture->GetObjectEntity()->GetID()) {
      break;
    }
  }
  
  if (it != ysorted_tree.end()) {
    ysorted_tree.erase(it);
    ysorted_tree.insert(pair<double, CObjectPicture*>(object_picture->GetRenderY() + object_picture->GetZIndex(), object_picture));
  }
}

CObjectPicture* CObjectRender::addPicture(CObjectEntity* object_entity, double z_index)
{
  CObjectPicture* object_picture = new CObjectPicture(object_sprite[object_entity->GetRootObject()->GetID()], object_entity, z_index);
  
  ysorted_tree.insert(pair<double, CObjectPicture*>(object_entity->GetY() + z_index - object_entity->GetRootObject()->GetYSize(), object_picture));
}

void CObjectRender::remPicture(int id)
{
  multimap<double, CObjectPicture*, less< double > >::iterator it; 
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetObjectEntity()->GetID() == id) {
      break;
    }
  }
  
  if (it != ysorted_tree.end()) {
    ysorted_tree.erase(it);
  }  
}

CObjectPicture* CObjectRender::GetObjectPicture(int object_id)
{
  multimap<double, CObjectPicture*, less< double > >::iterator it;
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetObjectEntity()->GetID() == object_id) {
      return it->second;
    }
  }
  
  return NULL;
}



