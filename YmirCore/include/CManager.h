/* 
 * File:   CManager.h
 * Author: Matej Pechac
 *
 * Created on September 19, 2014, 12:18 PM
 */

#ifndef CMANAGER_H
#define	CMANAGER_H

#include <IManager.h>
#include <CModule.h>
#include <CObjectManager.h>

template<class Type, class Entity>
class CManager : public IManager<Entity> {
  public:
  
  CManager(CModule<Type> *module, CObjectManager* object_manager) : IManager<Entity>() {
    this->type_module = module;
    this->object_manager = object_manager;
  };

  CManager(const CManager& orig) : IManager<Entity>(orig) {
    this->type_module = orig.type_module;
    this->object_manager = orig.object_manager;
  };

  virtual ~CManager() { };

protected:
  CModule<Type>         *type_module;
  CObjectManager*       object_manager;
};

#endif	/* CMANAGER_H */

