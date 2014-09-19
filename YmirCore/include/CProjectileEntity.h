/* 
 * File:   CProjectileEntity.h
 * Author: Matej Pechac
 *
 * Created on September 17, 2014, 10:42 PM
 */

#ifndef CPROJECTILEENTITY_H
#define	CPROJECTILEENTITY_H

#include "CObjectEntity.h"
#include "CProjectile.h"

class CProjectileEntity : public CObjectEntity {
public:
  CProjectileEntity(CProjectile* projectile, int inner_id, int x, int y, int target_x, int target_y);
  CProjectileEntity(const CProjectileEntity& orig);
  virtual ~CProjectileEntity();
  
  CProjectile*  GetRootProjectile() { return root_projectile; };
  int GetTargetX() { return target_x; };
  int GetTargetY() { return target_y; };
  int GetDeltaX() { return delta_x; };
  int GetDeltaY() { return delta_y; };
  
private:
  CProjectile* root_projectile;
  int target_x;
  int target_y;
  int delta_x;
  int delta_y;
};

#endif	/* CPROJECTILEENTITY_H */

