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
    DIE = 4
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
  
private:
  E_TYPE  type;
  int     x;
  int     y;
  CUnitEntity* target;
  int     cost;
  
  
};

#endif	/* CACTION_H */

