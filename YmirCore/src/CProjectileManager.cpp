/* 
 * File:   CProjectileManager.cpp
 * Author: Matej Pechac
 * 
 * Created on September 19, 2014, 11:59 AM
 */

#include "CProjectileManager.h"

CProjectileManager::CProjectileManager(CModule<CProjectile> *module) : CManager<CProjectile, CProjectileEntity>(module) {
}

CProjectileManager::CProjectileManager(const CProjectileManager& orig) : CManager<CProjectile, CProjectileEntity>(orig) {
}

CProjectileManager::~CProjectileManager() {
}

CProjectileEntity* CProjectileManager::Add(int x, int y, int id, CUnitEntity* target) {
  CObjectEntity* projectile = NULL;
  
  projectile = new CProjectileEntity(type_module->GetUnitPtr(id), 0, x, y, target);
  entity_list.push_back(reinterpret_cast<CProjectileEntity*>(projectile));
  
  return reinterpret_cast<CProjectileEntity*>(projectile);  
}

