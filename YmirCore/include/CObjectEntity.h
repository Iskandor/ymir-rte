/* 
 * File:   CObjectEntity.h
 * Author: Matej Pechac
 *
 * Created on May 10, 2014, 11:18 AM
 */

#ifndef COBJECTENTITY_H
#define	COBJECTENTITY_H

#include "CObject.h"

class CObjectEntity {
public:
  CObjectEntity(int inner_id);
  CObjectEntity(CObject* object, int inner_id, int x, int y);
  CObjectEntity(const CObjectEntity& orig);
  virtual ~CObjectEntity();
protected:
  unsigned int id;
  int x;
  int y;
  
  CObject*  root_object;
  CObjectEntity*  ref_object_entity;

public:  
  void SetID(unsigned int id) { this->id = id; };
  unsigned int GetID();
  int GetX();
  int GetY();
  
  void setPosition(int x, int y);

  static bool  CompareY(CObjectEntity &e1, CObjectEntity &e2);  
  
  CObject*  GetRootObject() { return root_object; };
  
  void SetRefObject(CObjectEntity* ref_object_entity) { this->ref_object_entity = ref_object_entity; };
  CObjectEntity* GetRefObject() {return ref_object_entity; };
};

#endif	/* COBJECTENTITY_H */

