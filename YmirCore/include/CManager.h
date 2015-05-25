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
  
  CManager(CModule<Type> *module) : IManager<Entity>() {
    this->type_module = module;
  };

  CManager(const CManager& orig) : IManager<Entity>(orig) {
    this->type_module = orig.type_module;
  };

  virtual ~CManager() { };

protected:
  CModule<Type> *type_module;
};

#endif	/* CMANAGER_H */

