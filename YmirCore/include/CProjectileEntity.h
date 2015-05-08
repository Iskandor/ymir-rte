/* 
 * File:   CProjectileEntity.h
 * Author: Matej Pechac
 *
 * Created on September 17, 2014, 10:42 PM
 */

#ifndef CPROJECTILEENTITY_H
#define	CPROJECTILEENTITY_H

#include "CObjectEntity.h"
#include "CUnitEntity.h"
#include "CProjectile.h"

class CProjectileEntity : public CObjectEntity {
public:
  CProjectileEntity(CProjectile* projectile, int inner_id, int x, int y, CUnitEntity* target);
  CProjectileEntity(const CProjectileEntity& orig);
  virtual ~CProjectileEntity();
  
  CProjectile*  GetRootProjectile() { return root_projectile; };
  int GetTargetX() { return target->GetX() + target->GetRootObject()->GetXSize() / 2; };
  int GetTargetY() { return target->GetY() + target->GetRootObject()->GetYSize() / 2; };
  int GetDeltaX() { return delta_x; };
  int GetDeltaY() { return delta_y; };
  int GetX() { return map_x; };
  int GetY() { return map_y; };
  
  void setPosition(int x, int y);
  
  
  CUnitEntity* GetTarget() { return target; };
  
private:
  CProjectile* root_projectile;
  CUnitEntity* target;
  int delta_x;
  int delta_y;
  
  int map_x;
  int map_y;
};

#endif	/* CPROJECTILEENTITY_H */

