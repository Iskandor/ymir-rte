/* 
 * File:   CGame.h
 * Author: matej
 *
 * Created on May 8, 2015, 10:42 PM
 */

#ifndef CGAME_H
#define	CGAME_H

#include "CMap.h"
#include "CMapRender.h"
#include "CDataManager.h"
#include "CPlayerManager.h"
#include "CTileRender.h"
#include "CUnitRender.h"
#include "CObjectRender.h"
#include "CProjectileRender.h"
#include "CUnitControls.h"
#include "CMapControls.h"
#include "CGameControls.h"
#include "CProjectileControls.h"
#include "CDataManager.h"
#include "CObjectBuilder.h"

class CGame {
  public:
    CGame(SDL_Surface* surfDisplay, SDL_Rect rectDisplay, CGuiManager* gui_manager, CFontRender* font_render);
    CGame(const CGame& orig);
    virtual ~CGame();
  private:
    SDL_Surface*    surfDisplay;
    SDL_Rect        rectDisplay;    
    
    CDataManager    data_manager;
    CMap            *map;
    CMapRender      *map_render;
    CObjectBuilder  *object_builder;

    CTileRender     *tile_render;
    CUnitRender     *unit_render;
    CObjectRender   *object_render;
    CProjectileRender *projectile_render;

    CMapControls        *map_controls;
    CUnitControls       *unit_controls;
    CGameControls       *game_controls;
    CProjectileControls *projectile_controls;  

    CPlayerManager  player_manager; 
    
    CFontRender     *font_render;
    CGuiManager     *gui_manager;    

  public:
    int     OnInit();
    void    OnEvent(SDL_Event* event);
    void    OnRender();
    void    OnLoop();    
};

#endif	/* CGAME_H */

