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
            }
            CObjectEntity* selector = map->addObject(unit_entity->GetX(), unit_entity->GetY(), BOTTOM, 0);
            unit_entity->SetRefObject(selector);
            selected_unit = unit_entity;
            break;
          }
        }
        if (i == map->GetUnitManager()->GetUnitListSize()) {
          if (selected_unit != NULL) {
            map->remObject(selected_unit->GetRefObject()->GetID());
            selected_unit->SetRefObject(NULL);
            selected_unit = NULL;
          }          
        }
      }
      if (event->button.button == SDL_BUTTON_RIGHT) {
        if (selected_unit != NULL) {
          SDL_Rect*    camera = map_render->GetCamera();
          int x = (event->button.x / MAP_ELEM) + camera->x - (selected_unit->GetRootObject()->GetXSize() / 2);
          int y = (event->button.y / MAP_ELEM) + camera->y - (selected_unit->GetRootObject()->GetYSize() - 1);
          map->Unblock(selected_unit);
          selected_unit->Move(map->GetCostMap(), map->getMapSizeX(sizemode_elem), map->getMapSizeY(sizemode_elem), x, y);
          map->Block(selected_unit);
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

