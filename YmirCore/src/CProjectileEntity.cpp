/* 
 * File:   CProjectileEntity.cpp
 * Author: Matej Pechac
 * 
 * Created on September 17, 2014, 10:42 PM
 */

#include "CProjectileEntity.h"
#include "CMathUtils.h"
#include <cmath>

CProjectileEntity::CProjectileEntity(CProjectile* projectile, int inner_id, int x, int y, int target_x, int target_y) : CObjectEntity(projectile, inner_id, x, y, 0) {
  this->root_projectile = projectile;
  this->target_x = target_x;
  this->target_y = target_y;
  
  delta_x = round(abs(target_x - x) / (CMathUtils::euclidian_distance(x, y, target_x, target_y) / projectile->GetSpeed()));
  delta_y = round(abs(target_y - y) / (CMathUtils::euclidian_distance(x, y, target_x, target_y) / projectile->GetSpeed()));
  
  if (target_x < x) {
    delta_x *= -1;
  }
  if (target_y < y) {
    delta_y *= -1;
  }
}

CProjectileEntity::CProjectileEntity(const CProjectileEntity& orig) : CObjectEntity(orig) {
  root_projectile = orig.root_projectile;
  target_x = orig.target_x;
  target_y = orig.target_y;
  delta_x = orig.delta_x;
  delta_y = orig.delta_y;
}

CProjectileEntity::~CProjectileEntity() {
}

