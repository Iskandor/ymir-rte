/* 
 * File:   CDataManager.cpp
 * Author: matej
 * 
 * Created on October 30, 2013, 9:15 PM
 */

#include "CDataManager.h"

CDataManager::CDataManager() {
}

CDataManager::CDataManager(const CDataManager& orig) {
}

CDataManager::~CDataManager() {
}

int CDataManager::OnInit()
{
  tile_module.LoadFromXML("data/tiles", "tiles", "tile");
  object_module.LoadFromXML("data/objects", "objects", "object"); 
  unit_module.LoadFromXML("data/units", "units", "unit");
  projectile_module.LoadFromXML("data/projectiles", "projectiles", "projectile");
  modifier_module.LoadFromXML("data/modifiers", "modifiers", "modifier");  
}

