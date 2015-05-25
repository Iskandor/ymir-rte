/* 
 * File:   CObjectPicture.cpp
 * Author: matej
 * 
 * Created on May 23, 2015, 11:17 AM
 */

#include "CObjectPicture.h"

CObjectPicture::CObjectPicture(CSprite* asset, CObjectEntity* object_entity, double z_index) : CPicture(asset, object_entity, z_index) {
}

CObjectPicture::CObjectPicture(const CObjectPicture& orig) : CPicture(orig) {
}

CObjectPicture::~CObjectPicture() { 
}

void CObjectPicture::OnRender(SDL_Surface* dest, SDL_Rect camera)
{
  CPicture::OnRender(dest, camera);
}

