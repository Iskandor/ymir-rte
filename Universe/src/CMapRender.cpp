/* 
 * File:   CMapRender.cpp
 * Author: Matej Pechac
 * 
 * Created on October 30, 2013, 9:15 PM
 */

#include "CMapRender.h"
#include "GlobalDefine.h"
#include "CUtils.h"

CMapRender::CMapRender(SDL_Rect* display_rect, CMap* map, CTileRender* tile_render, CUnitRender* unit_render) {
  camera.x = 0;
  camera.y = 0;
  camera.w = 20 * (TILE_W / MAP_ELEM);
  camera.h = 6 * (TILE_H / MAP_ELEM);
 
  main_rect = display_rect;  
  
  map_segments.clear();
  this->map = map;
  this->tile_render = tile_render;
  this->unit_render = unit_render;
  
  for(int i = 0; i < map->getMapSizeY(sizemode_segment); i++) {
    for(int j = 0; j < map->getMapSizeX(sizemode_segment); j++) {
      CMapSegment* segment = new CMapSegment(j, i, this->map, this->tile_render, this->unit_render);
      
      map_segments.push_back(segment);
    }
  }
}

CMapRender::CMapRender(const CMapRender& orig) {
  this->map = orig.map;
}

CMapRender::~CMapRender() {
}

void CMapRender::OnRender(SDL_Surface* dest) {
  for(int i = 0; i < map_segments.size(); i++) {
    CMapSegment* segment = map_segments[i];
    
    pair<int, int> upper_left(camera.x, camera.y);
    pair<int, int> upper_right((camera.x + camera.w), camera.y);
    pair<int, int> lower_left(camera.x, (camera.y + camera.h));
    pair<int, int> lower_right((camera.x + camera.w), (camera.y + camera.h));
    
    SDL_Rect  area;
    
    area.x = segment->GetX() * TILE_PER_SEGMENT * ELEM_PER_TILE;
    area.y = segment->GetY() * TILE_PER_SEGMENT * ELEM_PER_TILE;
    area.w = TILE_PER_SEGMENT * ELEM_PER_TILE;
    area.h = TILE_PER_SEGMENT * ELEM_PER_TILE;
    
    if (CUtils::PointIsInArea(upper_left, area) || 
        CUtils::PointIsInArea(upper_right, area) || 
        CUtils::PointIsInArea(lower_left, area) || 
        CUtils::PointIsInArea(lower_right, area)) {
      segment->OnRender(dest, &camera);
    }   
  }
  
  CUnitManager *unit_manager = map->GetUnitManager();

  for(int i = 0; i < unit_manager->GetUnitListSize(); i++) {
    CUnitEntity* unit_entity = unit_manager->getUnit(i);

    pair<int, int> point(unit_entity->GetX(), unit_entity->GetY());

    int x = (unit_entity->GetX() * MAP_ELEM) - (camera.x * MAP_ELEM);
    int y = (unit_entity->GetY() * MAP_ELEM) - (camera.y * MAP_ELEM);

    SDL_Rect camera_border;
    
    camera_border.x = camera.x - 4;
    camera_border.y = camera.y - 4;
    camera_border.w = camera.w + 8;
    camera_border.h = camera.h + 8;
    
    if (CUtils::PointIsInArea(point, camera_border)) {
      unit_render->OnRender(dest, unit_entity, x, y);
    }
  }   
}

SDL_Rect* CMapRender::GetCamera() {
  return &camera;
}

SDL_Rect* CMapRender::GetMainRect() {
  return main_rect;
}

CMap* CMapRender::GetMap() {
  return map;
}
