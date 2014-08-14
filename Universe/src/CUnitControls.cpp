/* 
 * File:   CUnitControls.cpp
 * Author: Matej Pechac
 * 
 * Created on April 12, 2014, 10:23 AM
 */

#include "CUnitControls.h"
#include "CMapRender.h"
#include "GlobalDefine.h"
#include "CUtils.h"
#include "CMathUtils.h"

CUnitControls::CUnitControls(CMapRender* map_render) {
  this->map_render = map_render; 
  this->map = map_render->GetMap();
}

CUnitControls::CUnitControls(const CUnitControls& orig) {
  map = orig.map;
}

CUnitControls::~CUnitControls() {
}

void CUnitControls::OnEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_MOUSEBUTTONUP:
      if (event->button.button == SDL_BUTTON_LEFT) {
        CUnitEntity* unit_entity = NULL;
        SDL_Rect     unit_rect;
        SDL_Rect*    camera;
        int i = 0;
        
        for(i = 0; i < map->GetUnitManager()->GetUnitListSize(); i++) {
          unit_entity = map->GetUnitManager()->getUnit(i);
          unit_rect.x = unit_entity->GetX();
          unit_rect.y = unit_entity->GetY();
          unit_rect.w = 4;
          unit_rect.h = 4;

          camera = map_render->GetCamera();

          pair<int, int> click;

          click.first = (event->button.x / MAP_ELEM) + camera->x;
          click.second = (event->button.y / MAP_ELEM) + camera->y;
          
          if (CUtils::PointIsInArea(click, unit_rect)) {
            if (selected_unit != NULL) {
              map->remObject(selected_unit->GetRefObject()->GetID());
              selected_unit->SetRefObject(NULL);
              selected_unit->SetSelected(false);
            }
            CObjectEntity* selector = map->addObject(unit_entity->GetX(), unit_entity->GetY(), BOTTOM, 0);
            unit_entity->SetRefObject(selector);
            selected_unit = unit_entity;
            /*
            map->Unblock(selected_unit);
            selected_unit->OnClick(map->GetCostMap(), map->getMapSizeX(sizemode_elem), map->getMapSizeY(sizemode_elem));
            map->Block(selected_unit);
             * */
            break;
          }
        }
        if (i == map->GetUnitManager()->GetUnitListSize()) {
          if (selected_unit != NULL) {
            map->remObject(selected_unit->GetRefObject()->GetID());
            selected_unit->SetRefObject(NULL);
            selected_unit->SetSelected(false);            
            selected_unit = NULL;

          }          
        }
      }
      if (event->button.button == SDL_BUTTON_RIGHT) {
        if (selected_unit != NULL) {
          SDL_Rect*    camera = map_render->GetCamera();
          int x = (event->button.x / MAP_ELEM) + camera->x;
          int y = (event->button.y / MAP_ELEM) + camera->y;
          CUnitEntity* other_unit = map->GetUnitManager()->getUnit(x, y);
          
          if (other_unit != NULL) {
              selected_unit->AddAction(CAction(CAction::ATTACK, other_unit, 1));
          }
          else
          {
            x = (event->button.x / MAP_ELEM) + camera->x - (selected_unit->GetRootObject()->GetXSize() / 2);
            y = (event->button.y / MAP_ELEM) + camera->y - (selected_unit->GetRootObject()->GetYSize() - 1);
             
            selected_unit->AddAction(CAction(CAction::CREATE_PATH, x, y, 0));
          }
        }
      }
    break;
  }
}

void CUnitControls::OnLoop() {
  CUnitEntity*  unit_entity = NULL;
  CAction       action;
  
  for(int i = 0; i < map->GetUnitManager()->GetUnitListSize(); i++) {
    unit_entity = map->GetUnitManager()->getUnit(i);
    action = unit_entity->GetAction();
    
    switch(action.GetType())
    {
        case CAction::IDLE:
            break;
        case CAction::CREATE_PATH:
            CreatePath(unit_entity, &action);
            break;
        case CAction::MOVE:
            Move(unit_entity, &action);
            break;
        case CAction::ATTACK:
            Attack(unit_entity, &action);
            break;
        case CAction::DIE:
            break;
    }
  }
}

void CUnitControls::CreatePath(CUnitEntity* unit_entity, CAction* action) {
    CreatePath(unit_entity, action->GetX(), action->GetY());
}

void CUnitControls::CreatePath(CUnitEntity* unit_entity, int x, int y) {
    map->Unblock(unit_entity);
    
    queue< pair<int, int> > path = GeneratePath(unit_entity, x, y);

    while(!path.empty()) {
        pair<int, int>  new_pos = path.front();
        unit_entity->AddAction(CAction(CAction::MOVE, new_pos.first, new_pos.second, 1));
        path.pop();
    }
    
    map->Block(unit_entity);
}

void CUnitControls::Move(CUnitEntity* unit_entity, CAction* action) {
    map->Unblock(unit_entity);

    if (unit_entity->GetX() > action->GetX()) {
      unit_entity->SetDirection(CUnitEntity::LEFT);
    }
    if (unit_entity->GetX() < action->GetX()) {
      unit_entity->SetDirection(CUnitEntity::RIGHT);
    }
    
    unit_entity->setPosition(action->GetX(), action->GetY());
    if (unit_entity->GetRefObject() != NULL) {
      unit_entity->GetRefObject()->setPosition(action->GetX(), action->GetY());
    }

    
    map->Block(unit_entity);
    map->SortObjects(unit_entity);
    if (unit_entity->GetRefObject() != NULL) {
      map->SortObjects(unit_entity->GetRefObject());
    }    
}
void CUnitControls::Attack(CUnitEntity* unit_entity, CAction* action) {
    map->Unblock(unit_entity);
    pair<int, int> target_pos = GetAttackPosition(selected_unit, action->GetTarget());
    map->Block(unit_entity);
                  
    CreatePath(unit_entity, target_pos.first, target_pos.second);
}

pair<int, int> CUnitControls::GetAttackPosition(CUnitEntity* attacker, CUnitEntity* target) {
  pair<double, double> target_pos = target->GetBlockCenter();
  pair<double, double> attacker_pos = attacker->GetBlockCenter();
  
  target_pos.first += target->GetX();
  target_pos.second += target->GetY();
  
  attacker_pos.first = attacker->GetX();
  attacker_pos.second = attacker->GetY();
  
  double min_value = 999;
  double min_x = 0;
  double min_y = 0;
  double act_value = min_value;
  double range_value = 0;
  
  for(int i = -attacker->GetRootUnit()->getAttackRange(); i < attacker->GetRootUnit()->getAttackRange(); i++) {
    for(int j = -attacker->GetRootUnit()->getAttackRange(); j < attacker->GetRootUnit()->getAttackRange(); j++) {
      act_value = CMathUtils::euclidian_distance(target_pos.first + j, target_pos.second + i, attacker_pos.first, attacker_pos.second);
      if (act_value < min_value) {
        range_value = CMathUtils::euclidian_distance(target_pos.first + j, target_pos.second + i, target_pos.first, target_pos.second);
        if (round(range_value) == attacker->GetRootUnit()->getAttackRange()) {
          if (map->IsPlaceFree(attacker, target->GetX() + j, target->GetY() + i)) {
            min_value = act_value;
            min_x = j;
            min_y = i;
          }
        }
      }
    }    
  }
  
  return pair<int, int>(min_x + target->GetX(), min_y + target->GetY());
}

queue< pair<int, int> > CUnitControls::GeneratePath(CUnitEntity* unit_entity, int x, int y) {
  set<int>   closed_set;
  set<int>   open_set;
  int*       came_from;
  
  double *g_score;
  double *f_score;
  
  queue< pair<int, int> > path;
  
  int size_x = map->getMapSizeX(SizeMode::sizemode_elem);
  int size_y = map->getMapSizeY(SizeMode::sizemode_elem);
  CUnit* root_unit = unit_entity->GetRootUnit();
  
  int length = size_x * size_y;
  
  g_score = new double[length];
  memset(g_score, 0, sizeof(double) * length);
  f_score = new double[size_x * size_y];
  memset(f_score, 0, sizeof(double) * length);
  came_from = new int[size_x * size_y];
  memset(came_from, -1, sizeof(int) * length);
  
  int sx = unit_entity->GetX();
  int sy = unit_entity->GetY();
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
      path = ReconstructPath(came_from, length, goal, size_x);
      return path;
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
              cost_sum += map->GetCostMap()[neighbor + (ik * size_x) + jk];
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
  
  return path;
}

queue< pair<int, int> > CUnitControls::ReconstructPath(int* came_from, int length, int current_node, int size_x) {
  if (came_from[current_node] != -1) {
    queue< pair<int, int> > p = ReconstructPath(came_from, length, came_from[current_node], size_x);
    p.push(CMap::decompose_node(current_node, size_x));
    return p;
  }
  else {
    queue< pair<int, int> > p;
    p.push(CMap::decompose_node(current_node, size_x));
    return p;
  }
}

