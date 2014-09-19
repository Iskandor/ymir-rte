/* 
 * File:   CUnitManager.cpp
 * Author: Matej Pechac
 * 
 * Created on August 21, 2012, 9:33 PM
 */

#include "CUnitManager.h"

CUnitManager::CUnitManager(CModule<CUnit> *unit_module, CObjectManager* object_manager) : CManager<CUnit, CUnitEntity>(unit_module, object_manager) {
}

CUnitManager::CUnitManager(const CUnitManager& orig) : CManager<CUnit, CUnitEntity>(orig) {
}

CUnitManager::~CUnitManager() {
}

CUnitEntity* CUnitManager::Add(int x, int y, int id, int player_id) {
  CObjectEntity* unit = NULL;
  
  unit = new CUnitEntity(type_module->GetUnitPtr(id), 0, player_id, x, y);
  
  object_manager->addObject(unit);
  entity_list.push_back(reinterpret_cast<CUnitEntity*>(unit));
  
  return reinterpret_cast<CUnitEntity*>(unit);
}

CUnitEntity* CUnitManager::Get(int x, int y) {
  CUnitEntity* result = NULL;
  
  for(int i = 0; i < entity_list.size(); i++) {
    result = entity_list[i];
    if (result->GetX() <= x && result->GetX() + result->GetRootUnit()->GetXSize() >= x &&
        result->GetY() <= y && result->GetY() + result->GetRootUnit()->GetYSize() >= y) {
      return result;
    }   
  }
  
  return NULL;
}

CUnitEntity* CUnitManager::Get(int index) {
  return CManager::Get(index);
}

CUnitEntity* CUnitManager::GetSelectedUnit() {
  for(int i = 0; i < entity_list.size(); i++) {
    if (((CUnitEntity*)entity_list[i])->GetSelected()) {
      return entity_list[i];
    }
  }
  return NULL;
}
