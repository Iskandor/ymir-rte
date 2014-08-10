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
class_name = "object_entity";  
}

CObjectEntity::CObjectEntity(CObject* object, int inner_id, int x, int y, double z_index) {
  id = inner_id;
  setPosition(x, y);
  this->z_index = z_index;
  root_object = object;
  state = IDLE;
  direction = CObjectEntity::RIGHT;
  class_name = "object_entity";
}

CObjectEntity::CObjectEntity(const CObjectEntity& orig) {
  id = orig.id;
  x = orig.x;
  y = orig.y;  
  z_index = orig.z_index;
  root_object = orig.root_object;
  
  state = orig.state;
  direction = orig.direction;
  class_name = orig.class_name;  
}

CObjectEntity::~CObjectEntity() {
}

void CObjectEntity::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

pair<int, int> CObjectEntity::FindFirstBlocked() {
  for(int i = 0; i < root_object->GetYSize(); i++) {
    for(int j = 0; j < root_object->GetXSize(); j++) {
      if (root_object->GetBlockMap()[i*root_object->GetXSize()+j] > 0) {
        return pair<int, int>(j, i);
      }
    }
  }
  return pair<int, int>(-1, -1);
}

pair<double, double> CObjectEntity::GetBlockCenter() {
  pair<double, double> result = FindFirstBlocked();
  
  for(int i = 0; i < root_object->GetYSize(); i++) {
    for(int j = 0; j < root_object->GetXSize(); j++) {
      if (root_object->GetBlockMap()[i*root_object->GetXSize()+j] > 0) {
        result.first += j;
        result.second += i;
        
        result.first /= 2;
        result.second /= 2;
      }
    }
  }
  
  return result;
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

