/* 
 * File:   CUnitEntity.cpp
 * Author: Matej Pechac
 * 
 * Created on February 6, 2013, 7:18 PM
 */

#include <set>

#include "CUnitEntity.h"
#include "CUtils.h"
#include "CMathUtils.h"
#include "CMap.h"

CUnitEntity::CUnitEntity(CUnit* unit, int inner_id, int player_id, int x, int y) : CObjectEntity(unit, inner_id, x, y, 0) {
  root_unit = unit;
  this->player_id = player_id;
  generate_props();
  selected = false;
  class_name = "unit_entity";
}

CUnitEntity::CUnitEntity(const CUnitEntity& orig) : CObjectEntity(orig) {
  root_unit = orig.root_unit;
  player_id = orig.player_id;
  max_hp = orig.max_hp;
  max_mp = orig.max_mp;
  hp = orig.hp;
  mp = orig.mp;
  sp = orig.sp;
  as = orig.as;
  selected = orig.selected;
  class_name = orig.class_name;
}

CUnitEntity::~CUnitEntity() {
}

void CUnitEntity::generate_props() {
  vector< int > props = root_unit->getProp();
  
  max_hp = props[END_IND]*5 + CUtils::rollDice(props[STR_IND], 1);
  hp = max_hp;
  max_mp = 0;
  mp = max_mp;
  max_sp = props[AGL_IND] + CUtils::rollDice(2, (props[AGL_IND] / 2));
  sp = max_sp;
  as = 0;
}

CUnit* CUnitEntity::GetRootUnit() {
  return root_unit;
}

void CUnitEntity::DecreaseSP(double value) {
  sp -= value;
}

void CUnitEntity::OnClick(double* block_map, int size_x, int size_y) {
  selected = true;
  generate_possible_loc(block_map, size_x, size_y);
}

void CUnitEntity::generate_possible_loc(double* block_map, int size_x, int size_y) {
  set<int>          closed_set;
  set<int>          open_set;
  map<int, double>     loc_cost;

  possible_loc.clear();
  pair<int, int> pos = FindFirstBlocked();
  pos.first += x;
  pos.second += y;
  int length = size_x * size_y;
  int current = CMap::compose_node(pos, size_x);;
  int neighbor = 0;
  double current_sp = 3; //= sp;
  double cost = 0;
  
  loc_cost[current] = current_sp;
  open_set.insert(current);
  closed_set.insert(current);
  
  while(!open_set.empty()) {
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if (i == 1 && j == 1) {
          continue;
        }
        if ( i == 1 || j == 1 ) {
          cost = 1;
        }
        else {
          cost = SQRT2;
        }
        
        neighbor = current + ((i-1) * size_x + (j-1));
        if (closed_set.count(neighbor) > 0 || neighbor < 0 || neighbor >= length) {
          continue;
        }
        if ((current_sp - (block_map[neighbor]+cost)) >= 0) {
          open_set.insert(neighbor);
          
          if (loc_cost.find(neighbor) == loc_cost.end()) {
            loc_cost[neighbor] = current_sp - (block_map[neighbor]+cost);
          }
          else if (loc_cost[neighbor] < (current_sp - (block_map[neighbor]+cost))) {
            loc_cost[neighbor] = current_sp - (block_map[neighbor]+cost);
          }
        }        
      }
    }
    current = *open_set.begin();
    current_sp = loc_cost[current];
    open_set.erase(current);
    closed_set.insert(current);
  }
  
  for(set<int>::iterator it = closed_set.begin(); it != closed_set.end(); it++) {
    possible_loc.insert(CMap::decompose_node(*it, size_x));
  }
}

void CUnitEntity::AddAction(CAction action) { 
  action.SetIndex(action_queue.size());
  action_queue.push(action);
}

CAction CUnitEntity::GetAction(bool pop) {
  CAction result;

  if (!action_queue.empty()) {
      result = action_queue.top();
      if (pop)
      {
        action_queue.pop();
      }
  }

  return result;
}

void CUnitEntity::ClearActionQueue() {
  while(!action_queue.empty()) {
    action_queue.pop();
  }
}

IModifier* CUnitEntity::AddModifier(IModifier* modifier) {
  modifier_list.push_back(modifier);
  
  return modifier_list[modifier_list.size() - 1];
}