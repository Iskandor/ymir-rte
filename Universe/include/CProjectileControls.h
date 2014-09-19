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

class CProjectileControls {
public:
  CProjectileControls(CMapRender* map_render);
  CProjectileControls(const CProjectileControls& orig);
  virtual ~CProjectileControls();
  
  void OnLoop();
  
private:
  void Move(CProjectileEntity* projectile_entity);
  void TargetReached(CProjectileEntity* projectile_entity);
  
private:
  CMapRender*   map_render;
  CMap*         map;
};

#endif	/* CPROJECTILECONTROL_H */

