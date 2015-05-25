/* 
 * File:   CProjectileRender.h
 * Author: Matej Pechac
 *
 * Created on May 21, 2015, 9:43 PM
 */

#ifndef CPROJECTILERENDER_H
#define	CPROJECTILERENDER_H


#include <SDL/SDL_image.h>

#include "IRender.h"
#include "CUnit.h"
#include "CModule.h"
#include "CProjectilePicture.h"

class CProjectileRender : public IRender<CProjectilePicture> {
public:
  CProjectileRender(CModule<CProjectile> *projectile_module);
  CProjectileRender(const CProjectileRender& orig);
  virtual ~CProjectileRender();
  
public:
  virtual bool LoadSurfaces();
  virtual CProjectilePicture* addPicture(CObjectEntity* object_entity, double z_index);
  
private:
  CModule<CProjectile> *projectile_module;
};

#endif	/* CPROJECTILERENDER_H */

