/* 
 * File:   CDataManager.h
 * Author: Matej Pechac
 *
 * Created on October 30, 2013, 9:15 PM
 */

#ifndef CDATAMANAGER_H
#define	CDATAMANAGER_H

#include "CTile.h"
#include "CUnit.h"
#include "CObject.h"
#include "CProjectile.h"
#include "CModifier.h"

#include "CModule.h"

class CDataManager {
  public:
    CDataManager();
    CDataManager(const CDataManager& orig);
    virtual ~CDataManager();
  private:
    CModule<CTile>        tile_module;  
    CModule<CUnit>        unit_module;  
    CModule<CObject>      object_module;  
    CModule<CProjectile>  projectile_module;
    CModule<CModifier>    modifier_module;
    
  public:
    int OnInit();
    
    CModule<CTile>* GetTileModule() { return &tile_module; };
    CModule<CUnit>* GetUnitModule() { return &unit_module; };
    CModule<CObject>* GetObjectModule() { return &object_module; };
    CModule<CProjectile>* GetProjectileModule() { return &projectile_module; };
    CModule<CModifier>* GetModifierModule() { return &modifier_module; };
};

#endif	/* CDATAMANAGER_H */

