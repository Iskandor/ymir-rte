/* 
 * File:   CManager.h
 * Author: Matej Pechac
 *
 * Created on September 19, 2014, 12:18 PM
 */

#ifndef CMANAGER_H
#define	CMANAGER_H

#include <CModule.h>
#include <CObjectManager.h>

template<class Type, class Entity>
class CManager {
  public:
  
  CManager(CModule<Type> *module, CObjectManager* object_manager) {
    this->type_module = module;
    this->object_manager = object_manager;
  };

  CManager(const CManager& orig) {
    this->type_module = orig.type_module;
    this->entity_list = orig.entity_list;
    this->object_manager = orig.object_manager;
  };

  virtual ~CManager() { };

  virtual Entity* Add() {};

  Entity* Get(int index) {
    return entity_list[index];
  };
 
  void Rem(int index) {
    int i = 0;
    typename vector<Entity*>::iterator it = entity_list.end();    

    for(it = entity_list.begin(); it != entity_list.end(); it++) {
      if (i == index) {
        entity_list.erase(it);
        break;
      }
      i++;
    }
  };

  void Rem(Entity* entity) {
    typename vector<Entity*>::iterator i = entity_list.end();

    for(i = entity_list.begin(); i != entity_list.end(); i++) {
      if (*i == entity) {
        break;
      }
    }

    if (i != entity_list.end()) {
      entity_list.erase(i);
    }
  };

  int GetListSize() {
    return entity_list.size();
  };
  
protected:
  CModule<Type>         *type_module;
  vector<Entity*>       entity_list;
  CObjectManager*       object_manager;
};

#endif	/* CMANAGER_H */

