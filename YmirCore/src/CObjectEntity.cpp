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
  root_object = NULL;
}

CObjectEntity::CObjectEntity(CObject* object, int inner_id, int x, int y) {
  id = inner_id;
  setPosition(x, y);
  root_object = object;
}

CObjectEntity::CObjectEntity(const CObjectEntity& orig) {
  id = orig.id;
  x = orig.x;
  y = orig.y;  
  root_object = orig.root_object;
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

bool CObjectEntity::CompareY(CObjectEntity &e1, CObjectEntity &e2) {
  return (e1.GetY() < e2.GetY());
}

