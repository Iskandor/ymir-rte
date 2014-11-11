/* 
 * File:   CApp.cpp
 * Author: Matej Pechac
 * 
 * Created on August 20, 2012, 3:58 PM
 */

#include "CApp.h"
#include "CMapRender.h"

CApp::CApp() {
  surfDisplay = NULL;

  running = true;
}

CApp::CApp(const CApp& orig) {
  running = orig.running;
}

CApp::~CApp() {
  delete map;
  delete tile_render;
  delete map_render;
  delete map_controls;
}

int CApp::OnExecute() {
  SDL_Event event;

  if (OnInit() != 0) {
    return -1;
  }
  
  const int FPS = 32;
  
  Uint32  start;

  while(running) {
    start = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }
    OnLoop();
    OnRender();
    
    if (1000/FPS > (SDL_GetTicks() - start)) {
      SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
    }
  }

  OnCleanup();

  return 0;
}

int CApp::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return -1;
  }
  
  if( TTF_Init() == -1 ) {
    return -2; 
  }

  font_render = new CFontRender();
  
  rectDisplay.x = rectDisplay.y = 0;
  rectDisplay.w = RESOLUTION_W;
  rectDisplay.h = RESOLUTION_H;
  
  if ((surfDisplay = SDL_SetVideoMode(rectDisplay.w, rectDisplay.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) { /*SDL_FULLSCREEN*/
    return -2;
  }
  
  gui_manager = new CGuiManager(surfDisplay, font_render);
  if (gui_manager->OnInit() != 0) {
    return -3;
  }
  
  tile_module.LoadFromXML("data/tiles", "tiles", "tile");
  tile_render = new CTileRender(&tile_module);
  
  object_module.LoadFromXML("data/objects", "objects", "object"); 
  unit_module.LoadFromXML("data/units", "units", "unit");
  projectile_module.LoadFromXML("data/projectiles", "projectiles", "projectile");
  modifier_module.LoadFromXML("data/modifiers", "modifiers", "modifier");
  
  
  for(int i = 0; i < unit_module.GetSize(); i++) {
    CObject object = unit_module.GetUnit(i);
    int new_obj_id = object_module.AddUnit(object);
    unit_module.GetUnitPtr(object.GetID())->SetID(new_obj_id);
  }
  
  for(int i = 0; i < projectile_module.GetSize(); i++) {
    CObject object = projectile_module.GetUnit(i);
    int new_obj_id = object_module.AddUnit(object);
    projectile_module.GetUnitPtr(object.GetID())->SetID(new_obj_id);
  }  
  
  object_render = new CObjectRender(&object_module, &unit_module, &projectile_module);  
  unit_render = new CUnitRender(&unit_module);
    
  map = new CMap(&tile_module, &unit_module, &object_module, &projectile_module);
  map->Load("data/maps/mapa1.map");
  player_manager.AddPlayer("Drow", "");
  player_manager.AddPlayer("Snake", "");
  map->SetPlayerManager(&player_manager);
  
  map->addUnit(5, 5, 1, 0);
  map->addUnit(7, 4, 2, 0);
  map->addUnit(10, 9, 3, 0);
  map->addUnit(3, 7, 4, 0);
  map->addUnit(4, 12, 6, 0);

  map->addUnit(15, 8, 5, 1);
  map->addUnit(17, 4, 5, 1);
  
  map_render = new CMapRender(&rectDisplay, map, tile_render, unit_render, object_render);
  map_controls = new CMapControls(map_render);
  unit_controls = new CUnitControls(map_render, gui_manager);
  unit_controls->SetCurrentPlayerID(0);
  unit_controls->SetModifierModule(&modifier_module);
  projectile_controls = new CProjectileControls(map_render);
  
  game_controls = new CGameControls(&player_manager, unit_controls);
  
  return 0;
}

void CApp::OnLoop() {
  map_controls->OnLoop();
  unit_controls->OnLoop();
  projectile_controls->OnLoop();
}

void CApp::OnEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_QUIT: {
      running = false;
    } break;
    case SDL_KEYUP: {
      if (event->key.keysym.sym == SDLK_q)
      {
        running = false;
      }      
    } break;
  }
  map_controls->OnEvent(event);
  unit_controls->OnEvent(event);
  game_controls->OnEvent(event);
  gui_manager->OnEvent(*event);
}

void CApp::OnRender() {
  SDL_FillRect(surfDisplay, NULL, SDL_MapRGB(surfDisplay->format, 0, 0, 0));
  map_render->OnRender(surfDisplay);
  gui_manager->OnRender();
  
  SDL_Rect   player_rect = {0, 0, 200, 32};
  SDL_Color  player_color = {255, 255, 255}; 
  
  font_render->RenderText(surfDisplay, player_rect, player_manager.GetPlayer(game_controls->GetCurrentPlayerID())->GetName(), player_color);
  
  SDL_Flip(surfDisplay);
}

void CApp::OnCleanup() {
  SDL_Quit();
  TTF_Quit();
}


