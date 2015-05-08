/* 
 * File:   CMapRender.cpp
 * Author: Matej Pechac
 * 
 * Created on October 30, 2013, 9:15 PM
 */

#include <CMathUtils.h>

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
    
    SDL_Rect  area;
    
    area.x = segment->GetX() * TILE_PER_SEGMENT * ELEM_PER_TILE;
    area.y = segment->GetY() * TILE_PER_SEGMENT * ELEM_PER_TILE;
    area.w = TILE_PER_SEGMENT * ELEM_PER_TILE;
    area.h = TILE_PER_SEGMENT * ELEM_PER_TILE;
    
    if (CMathUtils::intersect(area, camera))
    {
      segment->OnRender(dest, &camera);
    }
  }
  
  CUnitEntity* selected_unit = map->GetUnitManager()->GetSelectedUnit();
  
  if (selected_unit != NULL) {
    render_possible_loc(dest, selected_unit);
  }

  multimap<double, CObjectPicture*, less<double> >* ytree = object_render->GetYSortedTree();
  multimap<double, CObjectPicture*, less<double> >::iterator it;

  for(it = ytree->begin(); it != ytree->end(); it++) {
    CObjectPicture* object_picture = it->second;
   
    object_picture->OnRender(dest, camera);
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

void CMapRender::SortObjects(CObjectEntity* object_entity)
{
  CObjectPicture* object_picture = object_render->GetObjectPicture(object_entity->GetID());
  object_render->SortObjects(object_picture);
}
