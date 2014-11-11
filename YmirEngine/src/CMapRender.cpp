/* 
 * File:   CMapRender.cpp
 * Author: Matej Pechac
 * 
 * Created on October 30, 2013, 9:15 PM
 */

#include "CMapRender.h"
#include "GlobalDefine.h"
#include "CUtils.h"

CMapRender::CMapRender(SDL_Rect* display_rect, CMap* map, CTileRender* tile_render, CUnitRender* unit_render, CObjectRender* object_render) {
  camera.x = 0;
  camera.y = 0;
  camera.w = CAMERA_W * (TILE_W / MAP_ELEM);
  camera.h = CAMERA_H * (TILE_H / MAP_ELEM);
 
  main_rect = display_rect;

  tech_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, MAP_ELEM, MAP_ELEM, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
  SDL_FillRect(tech_surface, NULL, SDL_MapRGB(tech_surface->format, 128, 128, 0)); 
  SDL_SetAlpha(tech_surface, SDL_SRCALPHA, 64);
  tech_surface = SDL_DisplayFormat(tech_surface);
  
  tech_rect.w = MAP_ELEM;
  tech_rect.h = MAP_ELEM;  
  
  map_segments.clear();
  this->map = map;
  this->tile_render   = tile_render;
  this->unit_render   = unit_render;
  this->object_render = object_render;
  
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
  SDL_FreeSurface(tech_surface);
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
  
  CUnitEntity* selected_unit = map->GetUnitManager()->GetSelectedUnit();
  
  if (selected_unit != NULL) {
    render_possible_loc(dest, selected_unit);
  }
  
  CObjectManager *object_manager = (CObjectManager*)map;
  multimap<double, CObjectEntity*, less<double> >* ytree = object_manager->GetYSortedTree();
  multimap<double, CObjectEntity*, less<double> >::iterator it;

  for(it = ytree->begin(); it != ytree->end(); it++) {
    CObjectEntity* object_entity = it->second;

    pair<int, int> point(object_entity->GetX(), object_entity->GetY());

    int x = object_entity->GetRenderX() - (camera.x * MAP_ELEM);
    int y = object_entity->GetRenderY() - (camera.y * MAP_ELEM);

    SDL_Rect camera_border;
    
    camera_border.x = camera.x - 4;
    camera_border.y = camera.y - 4;
    camera_border.w = camera.w + 8;
    camera_border.h = camera.h + 8;
    
    if (CUtils::PointIsInArea(point, camera_border)) {
      object_render->OnRender(dest, object_entity, x, y);
    }    
  }
}

void CMapRender::render_possible_loc(SDL_Surface* dest, CUnitEntity* unit_entity) {
  set<pair<int, int> > *possible_loc = unit_entity->GetPossibleLoc();
  set<pair<int, int> >::iterator it;
  
  for(it = possible_loc->begin(); it != possible_loc->end(); it++) {
    pair<int, int> loc = *it;
    if (CUtils::PointIsInArea(loc, camera)) {
      tech_rect.x = (loc.first - camera.x) * MAP_ELEM;
      tech_rect.y = (loc.second - camera.y) * MAP_ELEM;
      SDL_BlitSurface(tech_surface, NULL, dest, &tech_rect); 
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
