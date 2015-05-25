/* 
 * File:   CProjectileRender.cpp
 * Author: Matej Pechac
 * 
 * Created on May 21, 2015, 9:43 PM
 */

#include "CProjectileRender.h"
#include <iostream>

CProjectileRender::CProjectileRender(CModule<CProjectile> *projectile_module) : IRender<CProjectilePicture>() {
  this->projectile_module = projectile_module;
  
  if (!LoadSurfaces()) {
    cout << "Error in loading projectile surfaces" << endl;
  }  
}

CProjectileRender::CProjectileRender(const CProjectileRender& orig) : IRender<CProjectilePicture>(orig) {
  this->projectile_module = orig.projectile_module;
}

CProjectileRender::~CProjectileRender() {
}

bool CProjectileRender::LoadSurfaces() {
  SDL_Surface *new_surf = NULL;
  
  if (projectile_module == NULL) {
    return false;
  }
  
  for(int i = 0; i < projectile_module->GetSize(); i++) {
    CProjectile projectile = projectile_module->GetUnit(i);
    string path = projectile.GetImage();

    new_surf = IMG_Load(path.c_str());
    if (new_surf == NULL) {
      return false;
    }
    else {
      sprite_map[projectile.GetID()] = new CSprite(new_surf, &projectile);
    }    
  }
  
  return true;
}

CProjectilePicture* CProjectileRender::addPicture(CObjectEntity* object_entity, double z_index)  {
    CProjectileEntity* projectile_entity = (CProjectileEntity*)object_entity;
  
    CProjectilePicture* picture = new CProjectilePicture(sprite_map[projectile_entity->GetRootObject()->GetID()], projectile_entity, z_index);
    
    picture_buffer.emplace_back(picture);
    
    return picture;
}


