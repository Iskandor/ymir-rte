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
#include <set>

using namespace std;

class CUnitEntity : public CObjectEntity {
public:
  CUnitEntity(CUnit* unit, int inner_id, int player_id, int x, int y);
  CUnitEntity(const CUnitEntity& orig);
  virtual ~CUnitEntity();
  
public:
  CUnit*  GetRootUnit();
  int     GetPlayerID() { return player_id; };
  set< pair<int, int> >* GetPossibleLoc() { return &possible_loc; };
  void    SetSelected(bool value) { selected = value; };
  bool    GetSelected() { return selected; };
  int     GetHP() { return hp; };
  int     GetMaxHP() { return max_hp; };
  
  void OnClick(double* block_map, int size_x, int size_y);
  void Move(double* block_map, int size_x, int size_y, int x, int y);
  void Move();
  
private:
  void generate_props();
  void generate_path(double* block_map, int size_x, int size_y, int x, int y);
  void generate_possible_loc(double* block_map, int size_x, int size_y);
  queue< pair<int, int> > reconstruct_path(int* came_from, int length, int current_node, int size_x);
  
private:
  /* unit root variable */
  CUnit*  root_unit;
  
  int player_id;
  /* generated props */
  int hp;
  int max_hp;
  int mp;
  int max_mp;
  double sp;
  double max_sp;
  double as;
  
  queue< pair<int, int> > path;
  set< pair<int, int> >   possible_loc;
  bool  selected;
};

#endif	/* CUNITENTITY_H */

