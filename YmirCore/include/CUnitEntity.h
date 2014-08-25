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
#include "CAction.h"
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
  void    SetHP(int value) { hp = value; };
  int     GetHP() { return hp; };
  int     GetMaxHP() { return max_hp; };
  void    AddAction(CAction action) { action_queue.push(action); };
  CAction GetAction();
  
  
  void OnClick(double* block_map, int size_x, int size_y);
  
private:
  void generate_props();
  void generate_possible_loc(double* block_map, int size_x, int size_y);
  
  
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
  
  queue<CAction>          action_queue;
  set< pair<int, int> >   possible_loc;
  bool  selected;
};

#endif	/* CUNITENTITY_H */

