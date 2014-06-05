/* 
 * File:   CEntityManager.cpp
 * Author: Matej Pechac
 * 
 * Created on August 21, 2012, 9:39 PM
 */

#include <limits>
#include <algorithm>

#include "CObjectManager.h"

CObjectManager::CObjectManager(CModule<CObject> *object_module) {
  new_ent_id = 0;
  set_ent_id.clear();
  this->object_module = object_module;
  ysorted_tree.clear();
}

CObjectManager::CObjectManager(const CObjectManager& orig) {
  new_ent_id = orig.new_ent_id;
  set_ent_id = orig.set_ent_id;
  object_module = orig.object_module;
  object_tree = orig.object_tree;
  ysorted_tree = orig.ysorted_tree;
}

CObjectManager::~CObjectManager() {
}

unsigned int CObjectManager::genNewEntId() {
  while(set_ent_id.count(new_ent_id) > 0 && new_ent_id < numeric_limits<unsigned int>::max()) {
    new_ent_id++;
  }
  
  return new_ent_id;
}

CObjectEntity* CObjectManager::addObject(int x, int y, double z_index, int class_id, CObject* object) {
  CObjectEntity* object_entity = NULL;
  
  if (class_id == -1 && object != NULL) {
    object_entity = new CObjectEntity(object, new_ent_id, x, y, z_index);
  }
  else if (class_id > -1) {
    object_entity = new CObjectEntity(object_module->GetUnitPtr(class_id), new_ent_id, x, y, z_index);
  }
  
  if (object_entity != NULL) {
    set_ent_id.insert(new_ent_id);
    object_list.emplace_back(object_entity);
    object_tree[new_ent_id] = object_entity;
    ysorted_tree.insert(pair<double, CObjectEntity*>(y + z_index - object_entity->GetRootObject()->GetYSize(), 
                                                    object_entity));
    genNewEntId();
  }
  
  return object_entity;
}

CObjectEntity* CObjectManager::addObject(CObjectEntity* object_entity) {
  object_entity->SetID(new_ent_id);
  set_ent_id.insert(new_ent_id);
  
  object_list.emplace_back(object_entity);
  object_tree[new_ent_id] = (object_entity);
  ysorted_tree.insert(pair<double, CObjectEntity*>(object_entity->GetY() + object_entity->GetZIndex() - object_entity->GetRootObject()->GetYSize(),
                                                  object_entity));
  genNewEntId();
  
  return object_entity;
}

void CObjectManager::remObject(int id) {
  multimap<double, CObjectEntity*, less< double > >::iterator it;
  pair<multimap<double, CObjectEntity*, less< double > >::iterator,
       multimap<double, CObjectEntity*, less< double > >::iterator> boundries;

  double key = object_tree[id]->GetY() + object_tree[id]->GetZIndex();  
  boundries = ysorted_tree.equal_range(key);
  
  for(it = boundries.first; it != boundries.second; it++) {
    if (it->second->GetID() == id) {
      break;
    }
  }
  
  if (it != boundries.second) {
    ysorted_tree.erase(it);
  }
  object_tree.erase(id);
  
  for(vector< unique_ptr<CObjectEntity> >::iterator i = object_list.begin(); i != object_list.end(); i++) {
    CObjectEntity* object_entity = NULL;
    if (((CObjectEntity)(**i)).GetID() == id) {
      object_list.erase(i);
      object_entity = (*i).release();
      delete object_entity;
      break;
    }
  }
  set_ent_id.erase(id);
}

CObjectEntity* CObjectManager::getObject(int id) {
  return object_tree[id];
}

CObjectEntity* CObjectManager::getObjectByIndex(int index) {
  return &(*object_list[index]);
}

int CObjectManager::GetObjectListSize() {
  return object_list.size();
}

void CObjectManager::SortObjects(CObjectEntity* object_entity) {
  multimap<double, CObjectEntity*, less< double > >::iterator it;
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetID() == object_entity->GetID()) {
      break;
    }
  }
  
  if (it != ysorted_tree.end()) {
    ysorted_tree.erase(it);
    ysorted_tree.insert(pair<double, CObjectEntity*>(object_entity->GetY() + object_entity->GetZIndex(), object_entity));
  }
  
  
}
