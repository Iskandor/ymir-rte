/* 
 * File:   CProjectileManager.h
 * Author: Matej Pechac
 *
 * Created on September 19, 2014, 11:59 AM
 */

#ifndef CPROJECTILEMANAGER_H
#define	CPROJECTILEMANAGER_H

#include "CModule.h"
#include "CManager.h"
#include "CProjectile.h"
#include "CUnitEntity.h"
#include "CProjectileEntity.h"
#include "CObjectManager.h"

class CProjectileManager : public CManager<CProjectile, CProjectileEntity> {
public:
  CProjectileManager(CModule<CProjectile> *module);
  CProjectileManager(const CProjectileManager& orig);
  virtual ~CProjectileManager();
public:
  CProjectileEntity* Add(int x, int y, int id, CUnitEntity* target);
};

#endif	/* CPROJECTILEMANAGER_H */

