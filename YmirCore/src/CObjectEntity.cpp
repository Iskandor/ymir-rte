/* 
 * File:   CObjectEntity.cpp
 * Author: Matej Pechac
 * 
 * Created on May 10, 2014, 11:18 AM
 */

#include "CObjectEntity.h"

CObjectEntity::CObjectEntity(int inner_id) {
  id = inner_id;
  x = y = 0;  
  z_index = 0;
  root_object = NULL;
  state = IDLE;
  direction = CObjectEntity::RIGHT;  
}

CObjectEntity::CObjectEntity(CObject* object, int inner_id, int x, int y, double z_index) {
  id = inner_id;
  setPosition(x, y);
  this->z_index = z_index;
  root_object = object;
  state = IDLE;
  direction = CObjectEntity::RIGHT;  
}

CObjectEntity::CObjectEntity(const CObjectEntity& orig) {
  id = orig.id;
  x = orig.x;
  y = orig.y;  
  z_index = orig.z_index;
  root_object = orig.root_object;
  
  state = orig.state;
  direction = orig.direction;  
}

CObjectEntity::~CObjectEntity() {
}

void CObjectEntity::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

int CObjectEntity::GetX() {
  return x;
}

int CObjectEntity::GetY() {
  return y;
}

unsigned int CObjectEntity::GetID() {
  return id;
}

bool CObjectEntity::operator <(CObjectEntity& ent) {
  if (this->y == ent.y) {
    return (this->z_index < ent.z_index);
  }
  else {
    return (this->y < ent.y);
  }
}

