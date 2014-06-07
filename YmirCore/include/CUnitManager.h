/* 
 * File:   CUnitManager.h
 * Author: Matej Pechac
 *
 * Created on August 21, 2012, 9:33 PM
 */

#ifndef CUNITMANAGER_H
#define	CUNITMANAGER_H

#include "CModule.h"
#include "CUnitEntity.h"
#include "CUnit.h"
#include "CObjectManager.h"

#include <vector>

using namespace std;

class CUnitManager {
public:
  CUnitManager(CModule<CUnit> *unit_module, CObjectManager* object_manager);
  CUnitManager(const CUnitManager& orig);
  virtual ~CUnitManager();

public:
  CUnitEntity*  addUnit(int x, int y, int id, int player_id);
  CUnitEntity*  getUnit(int index);
  void          remUnit(int index);
  
  int           GetUnitListSize();  
  
private:
  CModule<CUnit>      *unit_module;
  vector<CUnitEntity*> unit_list;
  CObjectManager*      object_manager;
};

#endif	/* CUNITMANAGER_H */

