/* 
 * File:   CProjectilePicture.cpp
 * Author: Matej Pechac
 * 
 * Created on May 4, 2015, 9:40 PM
 */

#include "CProjectilePicture.h"

CProjectilePicture::CProjectilePicture(CSprite* asset, CProjectileEntity* projectile_entity, double z_index) : CPicture(asset, object_entity, z_index) {
}

CProjectilePicture::CProjectilePicture(const CProjectilePicture& orig) : CPicture(orig) {
}

CProjectilePicture::~CProjectilePicture() {
}

