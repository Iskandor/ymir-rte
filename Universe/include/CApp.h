/* 
 * File:   CApp.h
 * Author: Matej Pechac
 *
 * Created on August 20, 2012, 3:58 PM
 */

#ifndef CAPP_H
#define	CAPP_H

#include <SDL/SDL.h>

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

class CApp {
public:
  CApp();
  CApp(const CApp& orig);
  virtual ~CApp();

private:
  CMap            *map;
  CMapRender      *map_render;
  CMapControls    *map_controls;
  CModule<CTile>  tile_module;
  CTileRender     *tile_render;
  CModule<CUnit>  unit_module;
  CUnitRender     *unit_render;
  CUnitControls   *unit_controls;
  CModule<CObject> object_module;
  CObjectRender   *object_render;
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

