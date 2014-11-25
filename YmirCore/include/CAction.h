/* 
 * File:   CAction.h
 * Author: Matej Pechac
 *
 * Created on August 6, 2014, 7:35 PM
 */

#ifndef CACTION_H
#define	CACTION_H

//#include "CUnitEntity.h"

class CUnitEntity;

class CAction {
public:
  enum E_TYPE {
    IDLE = 0,
    CREATE_PATH = 1,
    MOVE = 2,
    ATTACK = 3,
    FIGHT = 4,
    DIE = 5
  };
  
  enum E_PRIORITY {
    HIGHEST = 0,
    HIGH = 1,
    MIDDLE = 2,
    LOW = 3,
    LOWEST = 4
  };
  
  struct less_by_priority {
    bool operator()(CAction& lhs, CAction& rhs) const
    {
      if (lhs.GetPriority() == rhs.GetPriority()) {
        return lhs.GetIndex() > rhs.GetIndex();
      }
      else {
        return lhs.GetPriority() < rhs.GetPriority();
      }
    }  
  };  
  
  CAction();
  CAction(E_TYPE type, int cost);
  CAction(E_TYPE type, int x, int y, int cost);
  CAction(E_TYPE type, CUnitEntity* target, int cost);
  CAction(const CAction& orig);
  virtual ~CAction();
  
  E_TYPE GetType() { return type; };
  int GetX() { return x; };
  int GetY() { return y; };
  CUnitEntity* GetTarget() { return target; };
  int GetCost() { return cost; };
  void SetPriority(E_PRIORITY value) { priority = value; };
  E_PRIORITY GetPriority() { return priority; };
  void SetIndex(int value) { index = value; };
  int GetIndex() { return index; };
  
private:
  E_TYPE  type;
  int     x;
  int     y;
  CUnitEntity* target;
  int     cost;
  E_PRIORITY priority;
  int     index;
  
};

#endif	/* CACTION_H */

