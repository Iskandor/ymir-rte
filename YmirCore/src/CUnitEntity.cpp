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
  
  max_hp = CUtils::rollDice(4, props[STR_IND]) + CUtils::rollDice(5, props[END_IND]);
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

void CUnitEntity::Move() {
  if (!path.empty()) {
    int new_x = path.front().first;
    int new_y = path.front().second;
    setPosition(new_x, new_y);
    if (ref_object_entity != NULL) {
      ref_object_entity->setPosition(new_x, new_y);
    }
    
    path.pop();    
  }
  else {
    state = IDLE;
  }
}

void CUnitEntity::Move(double* block_map, int size_x, int size_y, int x, int y) {
  generate_path(block_map, size_x, size_y, x, y);
  state = MOVING;
  
  if (this->x > x) {
    direction = CUnitEntity::LEFT;
  }
  if (this->x < x) {
    direction = CUnitEntity::RIGHT;
  }
}

void CUnitEntity::OnClick(double* block_map, int size_x, int size_y) {
  selected = true;
  generate_possible_loc(block_map, size_x, size_y);
}

void CUnitEntity::generate_path(double* block_map, int size_x, int size_y, int x, int y) {
  set<int>   closed_set;
  set<int>   open_set;
  int*       came_from;
  
  double *g_score;
  double *f_score;
  
  int length = size_x * size_y;
  
  g_score = new double[length];
  memset(g_score, 0, sizeof(double) * length);
  f_score = new double[size_x * size_y];
  memset(f_score, 0, sizeof(double) * length);
  came_from = new int[size_x * size_y];
  memset(came_from, -1, sizeof(int) * length);
  
  int sx = this->x;
  int sy = this->y;
  int gx = x;
  int gy = y;
  
  int start = CMap::compose_node(pair<int, int>(sx, sy), size_x);
  int goal = CMap::compose_node(pair<int, int>(gx, gy), size_x);
  
  double tentative_g_score = 0;
  double cost_sum = 0;
  int current = 0;
  int neighbor = 0;
  pair<int, int> neighbor_nod;
  
  open_set.insert(start);
  g_score[start] = 0;
  f_score[start] = g_score[start] + CMathUtils::euclidian_distance(sx, sy, gx, gy);
  
  while(!open_set.empty()) {
    current = CMathUtils::find_min(&open_set, f_score);
    
    if (current == goal) {
      path = reconstruct_path(came_from, length, goal, size_x);
      return;
    }
    
    open_set.erase(current);
    closed_set.insert(current);
    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if (i == 1 && j == 1) {
          continue;
        }
        neighbor = current + ((i-1) * size_x + (j-1));
        if (closed_set.count(neighbor) > 0 || neighbor < 0 || neighbor >= length) {
          continue;
        }
        
        tentative_g_score = g_score[current] + CMathUtils::euclidian_distance(0,0,(j-1),(i-1));
        cost_sum = 0;
        
        for(int ik = 0; ik < root_unit->GetYSize(); ik++) {
          for(int jk = 0; jk < root_unit->GetXSize(); jk++) {
            if (root_unit->GetBlockMap()[ik*root_unit->GetYSize()+jk] > 0) {
              cost_sum += block_map[neighbor + (ik * size_x) + jk];
            }
          }
        }
        
        tentative_g_score += cost_sum;
        
        if (open_set.count(neighbor) == 0 || tentative_g_score < g_score[neighbor]) {
          neighbor_nod = CMap::decompose_node(neighbor, size_x);
          came_from[neighbor] = current;
          g_score[neighbor] = tentative_g_score;
          f_score[neighbor] = g_score[neighbor] + CMathUtils::euclidian_distance(neighbor_nod.first, neighbor_nod.second, gx, gy);
          if (open_set.count(neighbor) == 0) {
            open_set.insert(neighbor);
          }
        }
      }
    }
  }
  
  delete f_score;
  delete g_score;
  delete came_from;
}

queue< pair<int, int> > CUnitEntity::reconstruct_path(int* came_from, int length, int current_node, int size_x) {
  if (came_from[current_node] != -1) {
    queue< pair<int, int> > p = reconstruct_path(came_from, length, came_from[current_node], size_x);
    p.push(CMap::decompose_node(current_node, size_x));
    return p;
  }
  else {
    queue< pair<int, int> > p;
    p.push(CMap::decompose_node(current_node, size_x));
    return p;
  }
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