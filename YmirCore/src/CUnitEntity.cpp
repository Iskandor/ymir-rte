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

CUnitEntity::CUnitEntity(CUnit* unit, int inner_id, int x, int y) : CObjectEntity(unit, inner_id, x, y, 0) {
  root_unit = unit;
  
  //generateProps();
  max_hp = 0;
  hp = max_hp;
  max_mp = 0;
  mp = max_mp;
  sp = 0;
  as = 0;
}

CUnitEntity::CUnitEntity(const CUnitEntity& orig) : CObjectEntity(orig) {
  root_unit = orig.root_unit;
  
  max_hp = orig.max_hp;
  max_mp = orig.max_mp;
  hp = orig.hp;
  mp = orig.mp;
  sp = orig.sp;
  as = orig.as;
}

CUnitEntity::~CUnitEntity() {
}

void CUnitEntity::generate_props() {
  vector< int > props = root_unit->getProp();
  
  max_hp = CUtils::rollDice(4, (props[STR_IND] / 4)) + CUtils::rollDice(5, (props[END_IND] / 5));
  hp = max_hp;
  max_mp = CUtils::rollDice(3, (props[DIV_IND] / 3)) + CUtils::rollDice(6, (props[INT_IND] / 6));
  mp = max_mp;
  sp = CUtils::rollDice(2, (props[AGL_IND] / 3));
  as = 1 / CUtils::rollDice(2, (props[AGL_IND] / 2));
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
            cost_sum += block_map[neighbor + (ik * size_x) + jk];
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
