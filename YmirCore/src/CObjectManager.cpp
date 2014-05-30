/* 
 * File:   CEntityManager.cpp
 * Author: Matej Pechac
 * 
 * Created on August 21, 2012, 9:39 PM
 */

#include <limits>

#include "CObjectManager.h"

CObjectManager::CObjectManager(CModule<CObject> *object_module) {
  new_ent_id = 0;
  set_ent_id.clear();
  this->object_module = object_module;
}

CObjectManager::CObjectManager(const CObjectManager& orig) {
  new_ent_id = orig.new_ent_id;
  set_ent_id = orig.set_ent_id;
  object_module = orig.object_module;
  object_tree = orig.object_tree;
}

CObjectManager::~CObjectManager() {
}

unsigned int CObjectManager::genNewEntId() {
  while(set_ent_id.count(new_ent_id) > 0 && new_ent_id < numeric_limits<unsigned int>::max()) {
    new_ent_id++;
  }
  
  return new_ent_id;
}

CObjectEntity* CObjectManager::addObject(int x, int y, int class_id, CObject* object) {
  CObjectEntity* object_entity = NULL;
  
  if (class_id == -1 && object != NULL) {
    object_entity = new CObjectEntity(object, new_ent_id, x, y);
  }
  else if (class_id > -1) {
    object_entity = new CObjectEntity(object_module->GetUnitPtr(class_id), new_ent_id, x, y);
  }
  
  if (object_entity != NULL) {
    set_ent_id.insert(new_ent_id);
    object_tree[new_ent_id] = object_entity;
    genNewEntId();
  }
  
  return object_entity;
}

CObjectEntity* CObjectManager::addObject(CObjectEntity* object_entity) {
  object_entity->SetID(new_ent_id);
  set_ent_id.insert(new_ent_id);
  
  object_list.emplace_back(object_entity);
  object_tree[new_ent_id] = (object_entity);
  
  genNewEntId();
  
  return object_entity;
}

void CObjectManager::remObject(int id) {
  object_tree.erase(id);
}

CObjectEntity* CObjectManager::getObject(int id) {
  return object_tree[id];
}

int CObjectManager::GetObjectListSize() {
  return object_list.size();
}

