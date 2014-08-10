/* 
 * File:   CUnitManager.cpp
 * Author: Matej Pechac
 * 
 * Created on August 21, 2012, 9:33 PM
 */

#include "CUnitManager.h"

CUnitManager::CUnitManager(CModule<CUnit> *unit_module, CObjectManager* object_manager) {
  this->unit_module = unit_module;
  this->object_manager = object_manager;
}

CUnitManager::CUnitManager(const CUnitManager& orig) {
  this->unit_module = orig.unit_module;
  this->unit_list = orig.unit_list;
  this->object_manager = orig.object_manager;
}

CUnitManager::~CUnitManager() {
}

CUnitEntity* CUnitManager::addUnit(int x, int y, int id, int player_id) {
  CObjectEntity* unit = NULL;
  
  unit = new CUnitEntity(unit_module->GetUnitPtr(id), 0, player_id, x, y);
  
  object_manager->addObject(unit);
  unit_list.push_back(reinterpret_cast<CUnitEntity*>(unit));
  
  return reinterpret_cast<CUnitEntity*>(unit);
}

CUnitEntity* CUnitManager::getUnit(int index) {
  return unit_list[index];
}

CUnitEntity* CUnitManager::getUnit(int x, int y) {
  CUnitEntity* result = NULL;
  
  for(int i = 0; i < unit_list.size(); i++) {
    result = unit_list[i];
    if (result->GetX() <= x && result->GetX() + result->GetRootUnit()->GetXSize() >= x &&
        result->GetY() <= y && result->GetY() + result->GetRootUnit()->GetYSize() >= y) {
      return result;
    }   
  }
  
  return NULL;
}

CUnitEntity* CUnitManager::getSelectedUnit() {
  for(int i = 0; i < unit_list.size(); i++) {
    if (unit_list[i]->GetSelected()) {
      return unit_list[i];
    }
  }
  return NULL;
}

void CUnitManager::remUnit(int index) {
  int i = 0;
  
  /*
  for(vector<CUnitEntity>::iterator it = unit_list.begin(); it != unit_list.end(); it++) {
    if (i == index) {
      unit_list.erase(it);
      break;
    }
    i++;
  }
   * */
}

int CUnitManager::GetUnitListSize() {
  return unit_list.size();
}

