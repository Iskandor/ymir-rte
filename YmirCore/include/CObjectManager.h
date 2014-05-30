/* 
 * File:   CEntityManager.h
 * Author: Matej Pechac
 *
 * Created on August 21, 2012, 9:39 PM
 */

#ifndef CENTITYMANAGER_H
#define	CENTITYMANAGER_H

#include <vector>
#include <set>
#include <map>
#include <memory>
#include "CModule.h"
#include "CObject.h"
#include "CObjectEntity.h"

using namespace std;

class CObjectManager {
public:
    CObjectManager(CModule<CObject> *object_module);
    CObjectManager(const CObjectManager& orig);
    virtual ~CObjectManager();
private:
    unsigned int        new_ent_id;
    set<unsigned int>   set_ent_id;  

private:
    unsigned int genNewEntId();

public:
    CObjectEntity*  addObject(int x, int y, int class_id, CObject* object = NULL);
    CObjectEntity*  addObject(CObjectEntity* object_entity);
    void            remObject(int id);
    CObjectEntity*  getObject(int id);
    int             GetObjectListSize();
    void            SortObjects();
  
  
private:
  CModule<CObject>  *object_module;
  
  vector< std::unique_ptr<CObjectEntity> > object_list;
  map<int, CObjectEntity*>  object_tree;
};

#endif	/* CENTITYMANAGER_H */

