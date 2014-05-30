/* 
 * File:   CMapSegment.cpp
 * Author: Matej Pechac
 * 
 * Created on October 31, 2013, 12:13 PM
 */

#include "CMapSegment.h"
#include "GlobalDefine.h"
#include "CMapRender.h"
#include "CUtils.h"

CMapSegment::CMapSegment(int x, int y, CMap* map, CTileRender* tile_render, CUnitRender*  unit_render) {
  this->x = x;
  this->y = y;
  this->map = map;
  this->tile_render = tile_render;
  this->unit_render = unit_render;
  
  main_rect.x = x * TILE_PER_SEGMENT * TILE_W;
  main_rect.y = y * TILE_PER_SEGMENT * TILE_H;
  main_rect.w = X_DIM;
  main_rect.h = Y_DIM;
  
  elem_rect.x = x * TILE_PER_SEGMENT * ELEM_PER_TILE;
  elem_rect.y = y * TILE_PER_SEGMENT * ELEM_PER_TILE;
  elem_rect.w = TILE_PER_SEGMENT * ELEM_PER_TILE;
  elem_rect.h = TILE_PER_SEGMENT * ELEM_PER_TILE;
  
  main_surf = SDL_CreateRGBSurface(SDL_SWSURFACE, X_DIM, Y_DIM, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
}

CMapSegment::CMapSegment(const CMapSegment& orig) {
  this->x = orig.x;
  this->y = orig.y;
  this->map = orig.map;
}

CMapSegment::~CMapSegment() {
  SDL_FreeSurface(main_surf);
}

void CMapSegment::OnRender(SDL_Surface* dest, SDL_Rect* camera) {
  int start_x = x * TILE_PER_SEGMENT;
  int start_y = y * TILE_PER_SEGMENT;
  // dopracovat orezavanie
  main_rect.x = ((start_x * TILE_W) - (camera->x * MAP_ELEM));
  main_rect.y = ((start_y * TILE_H) - (camera->y * MAP_ELEM));
  main_rect.w = (TILE_PER_SEGMENT * TILE_W); //(start_x * TILE_W) + (TILE_PER_SEGMENT * TILE_W) - (camera->x * MAP_ELEM * TILE_W);
  main_rect.h = (TILE_PER_SEGMENT * TILE_H); //(start_y * TILE_H) + (TILE_PER_SEGMENT * TILE_H) - (camera->y * MAP_ELEM * TILE_H);
  
  SDL_Rect block;
  block.w = MAP_ELEM;
  block.h = MAP_ELEM;
        
  for(int i = 0; i < TILE_PER_SEGMENT; i++) {
    for(int j = 0; j < TILE_PER_SEGMENT; j++) {
      int x_coor = j * TILE_W;
      int y_coor = i * TILE_H; // 
      
      tile_render->OnRender(main_surf, map->getTilePtr()[((start_y + i) * map->getMapSizeX(sizemode_tile) + (start_x + j))], x_coor, y_coor);
      
      /* zobrazovanie blokovanych casti na DEBUG ucely
      for(int ik = 0; ik < ELEM_PER_TILE; ik++) {
        for(int jk = 0; jk < ELEM_PER_TILE; jk++) {
          int node = ((start_y + i) * map->getMapSizeX(sizemode_elem) * ELEM_PER_TILE + ik) + (start_x + j) * ELEM_PER_TILE + jk;
          if (map->GetCostMap()[node] > 50) {
            pair<int, int> node_xy = CMap::decompose_node(node, map->getMapSizeX(sizemode_elem));
            //block.x = x_coor + (jk * MAP_ELEM);
            //block.y = y_coor + (ik * MAP_ELEM);
            block.x = node_xy.first * MAP_ELEM;
            block.y = node_xy.second * MAP_ELEM;
            
            SDL_FillRect(main_surf, &block, SDL_MapRGB(main_surf->format, 255, 0, 0));
          }
        }        
      }
       * */
    }
  }
   
  SDL_BlitSurface(main_surf, NULL, dest, &main_rect);
}

int CMapSegment::GetX() {
  return x;
}

int CMapSegment::GetY() {
  return y;
}


