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
            map->Unblock(selected_unit);
            selected_unit->OnClick(map->GetCostMap(), map->getMapSizeX(sizemode_elem), map->getMapSizeY(sizemode_elem));
            map->Block(selected_unit);
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
            pair<int, int> target_pos = GetAttackPosition(selected_unit, other_unit);
            map->Unblock(selected_unit);
            selected_unit->Move(map->GetCostMap(), map->getMapSizeX(sizemode_elem), map->getMapSizeY(sizemode_elem), target_pos.first, target_pos.second);
            map->Block(selected_unit);            
          }
          else
          {
            x = (event->button.x / MAP_ELEM) + camera->x - (selected_unit->GetRootObject()->GetXSize() / 2);
            y = (event->button.y / MAP_ELEM) + camera->y - (selected_unit->GetRootObject()->GetYSize() - 1);
             
            map->Unblock(selected_unit);
            selected_unit->Move(map->GetCostMap(), map->getMapSizeX(sizemode_elem), map->getMapSizeY(sizemode_elem), x, y);
            map->Block(selected_unit);
          }
        }
      }
    break;
  }
}

void CUnitControls::OnLoop() {
  CUnitEntity* unit_entity = NULL;
  
  for(int i = 0; i < map->GetUnitManager()->GetUnitListSize(); i++) {
    unit_entity = map->GetUnitManager()->getUnit(i);
    
    if (unit_entity->GetState() == CUnitEntity::MOVING) {
      map->Unblock(unit_entity);
      unit_entity->Move();
      map->Block(unit_entity);
      map->SortObjects(unit_entity);
      if (unit_entity->GetRefObject() != NULL) {
        map->SortObjects(unit_entity->GetRefObject());
      }
    }
  }
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

