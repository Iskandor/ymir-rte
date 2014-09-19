/* 
 * File:   CProjectileControl.cpp
 * Author: Matej Pechac
 * 
 * Created on September 19, 2014, 3:37 PM
 */

#include "CProjectileControls.h"

CProjectileControls::CProjectileControls(CMapRender* map_render) {
  this->map_render = map_render;
  this->map = map_render->GetMap();
}

CProjectileControls::CProjectileControls(const CProjectileControls& orig) {
  map_render = orig.map_render;
  map = orig.map;
}

CProjectileControls::~CProjectileControls() {
}

void CProjectileControls::OnLoop() { 
  for(int i = 0; i < map->GetProjectileManager()->GetListSize(); i++) {
    TargetReached(map->GetProjectileManager()->Get(i));
    Move(map->GetProjectileManager()->Get(i));
  }
}

void CProjectileControls::Move(CProjectileEntity* projectile_entity) {
  int delta_x = projectile_entity->GetDeltaX();
  int delta_y = projectile_entity->GetDeltaY();
  
  if (abs(projectile_entity->GetX() - projectile_entity->GetTargetX()) < abs(delta_x) )  {
    delta_x = abs(projectile_entity->GetX() - projectile_entity->GetTargetX()) * (projectile_entity->GetX() > projectile_entity->GetTargetX() ? -1 : 1);
  }
  if (abs(projectile_entity->GetY() - projectile_entity->GetTargetY()) < abs(delta_y) )  {
    delta_y = abs(projectile_entity->GetY() - projectile_entity->GetTargetY()) * (projectile_entity->GetY() > projectile_entity->GetTargetY() ? -1 : 1);
  }
  
  projectile_entity->setPosition(projectile_entity->GetX() + delta_x, projectile_entity->GetY() + delta_y);
}

void CProjectileControls::TargetReached(CProjectileEntity* projectile_entity) {
  if (projectile_entity->GetX() == projectile_entity->GetTargetX() && projectile_entity->GetY() == projectile_entity->GetTargetY()) {
    map->remProj(projectile_entity);
  }
}

