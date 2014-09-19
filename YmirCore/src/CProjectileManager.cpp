/* 
 * File:   CProjectileManager.cpp
 * Author: Matej Pechac
 * 
 * Created on September 19, 2014, 11:59 AM
 */

#include "CProjectileManager.h"

CProjectileManager::CProjectileManager(CModule<CProjectile> *module, CObjectManager* object_manager) : CManager<CProjectile, CProjectileEntity>(module, object_manager) {
}

CProjectileManager::CProjectileManager(const CProjectileManager& orig) : CManager(orig) {
}

CProjectileManager::~CProjectileManager() {
}

CProjectileEntity* CProjectileManager::Add(int x, int y, int id, int target_x, int target_y) {
  CObjectEntity* projectile = NULL;
  
  projectile = new CProjectileEntity(type_module->GetUnitPtr(id), 0, x, y, target_x, target_y);
  
  object_manager->addObject(projectile);
  entity_list.push_back(reinterpret_cast<CProjectileEntity*>(projectile));
  
  return reinterpret_cast<CProjectileEntity*>(projectile);  
}

