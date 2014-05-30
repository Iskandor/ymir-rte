/* 
 * File:   CUnitModuleManager.h
 * Author: Matej Pechac
 *
 * Created on June 30, 2013, 4:55 PM
 */

#ifndef CUNITMODULEMANAGER_H
#define	CUNITMODULEMANAGER_H

#include <vector>
#include <string>

#include "CModule.h"
#include "CUnit.h"

using namespace std;

class CUnitModuleManager {
public:
  CUnitModuleManager();
  CUnitModuleManager(string filename);
  CUnitModuleManager(const CUnitModuleManager& orig);
  virtual ~CUnitModuleManager();
  
  void  addUnitModule(CModule<CUnit> um);
  
  void  saveToFile(string filename);
  void  loadFromFile(string filename);
  
private:
  vector< CModule<CUnit> >  um_list;
  
};

#endif	/* CUNITMODULEMANAGER_H */

