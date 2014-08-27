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
  CObjectEntity(CObject* object, int inner_id, int x, int y, double z_index);
  CObjectEntity(const CObjectEntity& orig);
  virtual ~CObjectEntity();
  
  enum E_STATE {
    IDLE,
    MOVING
  };
  
  enum E_DIRECTION {
    RIGHT = 0,
    LEFT  = 1
  };
  
protected:
  unsigned int id;
  int x;
  int y;
  double z_index;
  
  E_STATE     state;
  E_DIRECTION direction;  
  
  CObject*  root_object;
  CObjectEntity*  ref_object_entity;
  
  string class_name;
  
protected:
  pair<int, int> FindFirstBlocked();

public:  
  void SetID(unsigned int id) { this->id = id; };
  unsigned int GetID();
  int GetX();
  int GetY();
  string GetClassName() { return class_name; };
  
  void setPosition(int x, int y);
  pair<double, double> GetBlockCenter();
  pair<double, double> GetNearestBlocked(CObjectEntity* object_entity);

  bool operator< (CObjectEntity& ent);  
  
  CObject*  GetRootObject() { return root_object; };
  
  void SetRefObject(CObjectEntity* ref_object_entity) { this->ref_object_entity = ref_object_entity; };
  CObjectEntity* GetRefObject() {return ref_object_entity; };
  
  void SetZIndex(int z_index) { this->z_index = z_index; };
  double GetZIndex() { return z_index; };
  
  E_DIRECTION GetDirection()  {return direction; };
  void SetDirection(E_DIRECTION value) { direction = value; };
  
  E_STATE     GetState()      {return state; };  
};

#endif	/* COBJECTENTITY_H */

