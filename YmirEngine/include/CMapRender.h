/* 
 * File:   CMapRender.h
 * Author: Matej Pechac
 *
 * Created on October 30, 2013, 9:15 PM
 */

#ifndef CMAPRENDER_H
#define	CMAPRENDER_H

#include <SDL/SDL.h>

#include "CMap.h"
#include "CMapSegment.h"
#include "CPictureRender.h"
#include "CTileRender.h"
#include "CUnitRender.h"
#include "CObjectRender.h"
#include "CProjectileRender.h"


using namespace std;

class CMapRender {
public:
  CMapRender(SDL_Rect* ,CMap* map, CTileRender* tile_render, CUnitRender* unit_render, CObjectRender* object_render, CProjectileRender* projectile_render);
  CMapRender(const CMapRender& orig);
  virtual ~CMapRender();
  
public:
  void OnRender(SDL_Surface* dest);
  
  SDL_Rect*  GetCamera();
  SDL_Rect*  GetMainRect();
  CMap*      GetMap();
  
  void SortObjects(CObjectEntity* object_entity);
  
  void  AddObject(CObjectEntity* object_entity, double z_index);
  void  RemObject(int id);
  void  AddUnit(CUnitEntity* unit_entity, double z_index);
  void  RemUnit(int id);
  void  AddProjectile(CProjectileEntity* projectile_entity, double z_index);
  void  RemProjectile(int id);
  
private:
  void render_possible_loc(SDL_Surface* dest, CUnitEntity* unit_entity);
  
private:
  SDL_Rect      camera;
  
  SDL_Surface*  main_surf;
	SDL_Rect*     main_rect;
  
  SDL_Surface*  tech_surface;
  SDL_Rect      tech_rect;
  
  CMap*           map;
  
  CTileRender*        tile_render;
  CUnitRender*        unit_render;
  CObjectRender*      object_render;
  CProjectileRender*  projectile_render;  
  
  CPictureRender* picture_render;
  
  vector<CMapSegment*>  map_segments;
};

#endif	/* CMAPRENDER_H */

