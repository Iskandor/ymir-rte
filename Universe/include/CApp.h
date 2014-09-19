/* 
 * File:   CApp.h
 * Author: Matej Pechac
 *
 * Created on August 20, 2012, 3:58 PM
 */

#ifndef CAPP_H
#define	CAPP_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "CModule.h"
#include "CTile.h"
#include "CTileRender.h"
#include "CUnit.h"
#include "CUnitRender.h"
#include "CUnitControls.h"
#include "CMap.h"
#include "CMapRender.h"
#include "CMapControls.h"
#include "CObject.h"
#include "CPlayerManager.h"
#include "CGuiManager.h"
#include "CGameControls.h"
#include "CFontRender.h"
#include "CProjectile.h"
#include "CProjectileControls.h"

class CApp {
public:
  CApp();
  CApp(const CApp& orig);
  virtual ~CApp();

private:
  CModule<CTile>        tile_module;  
  CModule<CUnit>        unit_module;  
  CModule<CObject>      object_module;  
  CModule<CProjectile>  projectile_module;
  
  CMap            *map;
  
  CMapControls        *map_controls;
  CUnitControls       *unit_controls;
  CGameControls       *game_controls;
  CProjectileControls *projectile_controls;
  
  
  CMapRender      *map_render;
  CTileRender     *tile_render;
  CUnitRender     *unit_render;
  CObjectRender   *object_render;
  CFontRender     *font_render;
  
  CPlayerManager  player_manager;
  CGuiManager     *gui_manager;
  
  bool running;

  SDL_Surface*    surfDisplay;
  SDL_Rect        rectDisplay;

public:
  int     OnExecute();
  int     OnInit();
  void    OnEvent(SDL_Event* event);
  void    OnRender();
  void    OnCleanup();
  void    OnLoop();
};

#endif	/* CAPP_H */

