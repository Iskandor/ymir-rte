/* 
 * File:   CProjectilePicture.h
 * Author: matej
 *
 * Created on May 4, 2015, 9:40 PM
 */

#ifndef CPROJECTILEPICTURE_H
#define	CPROJECTILEPICTURE_H

#include "CObjectPicture.h"
#include "CProjectileEntity.h"

class CProjectilePicture : public CObjectPicture {
public:
  CProjectilePicture(CSprite* asset, CProjectileEntity* projectile_entity, double z_index);
  CProjectilePicture(const CProjectilePicture& orig);
  virtual ~CProjectilePicture();
private:

};

#endif	/* CPROJECTILEPICTURE_H */

