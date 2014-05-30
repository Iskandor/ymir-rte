/* 
 * File:   CUnitEntity.h
 * Author: Matej Pechac
 *
 * Created on February 6, 2013, 7:18 PM
 */

#ifndef CUNITENTITY_H
#define	CUNITENTITY_H

#include "CObjectEntity.h"
#include "CUnit.h"
#include <string>
#include <vector>
#include <queue>

using namespace std;

class CUnitEntity : public CObjectEntity {
public:
  CUnitEntity(CUnit* unit, int inner_id, int x, int y);
  CUnitEntity(const CUnitEntity& orig);
  virtual ~CUnitEntity();
  
  enum E_STATE {
    IDLE,
    MOVING
  };

  enum E_DIRECTION {
    RIGHT = 0,
    LEFT  = 1
  };  

public:
  CUnit*  GetRootUnit();
  
  void Move(double* block_map, int size_x, int size_y, int x, int y);
  void Move();
  
  E_STATE     GetState()      {return state; };
  E_DIRECTION GetDirection()  {return direction; };
  
  void SetDirection(E_DIRECTION value) { direction = value; };
  
private:
  void generate_props();
  void generate_path(double* block_map, int size_x, int size_y, int x, int y);
  queue< pair<int, int> > reconstruct_path(int* came_from, int length, int current_node, int size_x);
  
private:
  /* unit root variable */
  CUnit*  root_unit;
  /* generated props */
  int hp;
  int max_hp;
  int mp;
  int max_mp;
  int sp;
  double as;
  
  queue< pair<int, int> > path;
  E_STATE     state;
  E_DIRECTION direction;
};

#endif	/* CUNITENTITY_H */

