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
#include "CManager.h"

#include <vector>

using namespace std;

class CUnitManager : public CManager<CUnit, CUnitEntity> {
public:
  CUnitManager(CModule<CUnit> *unit_module);
  CUnitManager(const CUnitManager& orig);
  virtual ~CUnitManager();

public:
  CUnitEntity*  Add(int x, int y, int id, int player_id);
  CUnitEntity*  Get(int x, int y);
  CUnitEntity*  Get(int index);  
  CUnitEntity*  GetSelectedUnit();
};

#endif	/* CUNITMANAGER_H */

