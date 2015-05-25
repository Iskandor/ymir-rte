/* 
 * File:   CProjectileControl.h
 * Author: matej
 *
 * Created on September 19, 2014, 3:37 PM
 */

#ifndef CPROJECTILECONTROL_H
#define	CPROJECTILECONTROL_H

#include "CMap.h"
#include "CMapRender.h"
#include "CProjectileEntity.h"
#include "CControls.h"

class CProjectileControls : public CControls {
public:
  CProjectileControls(CMap* map, CMapRender* map_render, CObjectBuilder* object_builder);
  CProjectileControls(const CProjectileControls& orig);
  virtual ~CProjectileControls();
  
  void OnLoop();
  
private:
  void Move(CProjectileEntity* projectile_entity);
  void TargetReached(CProjectileEntity* projectile_entity);
};

#endif	/* CPROJECTILECONTROL_H */

