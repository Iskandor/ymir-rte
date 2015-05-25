/* 
 * File:   CGame.cpp
 * Author: matej
 * 
 * Created on May 8, 2015, 10:42 PM
 */

#include "CGame.h"

CGame::CGame(SDL_Surface* surfDisplay, SDL_Rect rectDisplay, CGuiManager* gui_manager, CFontRender* font_render) {
  this->surfDisplay = surfDisplay;
  this->rectDisplay = rectDisplay;
  this->gui_manager = gui_manager;
  this->font_render = font_render;
}

CGame::CGame(const CGame& orig) {
}

CGame::~CGame() {
  delete map;
  delete tile_render;
  delete object_render;
  delete unit_render;
  delete map_render;
  delete map_controls;
  delete unit_controls;
  delete game_controls;
}

int CGame::OnInit()
{
  data_manager.OnInit();
  
  CModule<CTile>        *tile_module = data_manager.GetTileModule();  
  CModule<CUnit>        *unit_module = data_manager.GetUnitModule();  
  CModule<CObject>      *object_module = data_manager.GetObjectModule();  
  CModule<CProjectile>  *projectile_module = data_manager.GetProjectileModule();
  CModule<CModifier>    *modifier_module = data_manager.GetModifierModule();
  
  tile_render = new CTileRender(tile_module);
  
  for(int i = 0; i < unit_module->GetSize(); i++) {
    CObject object = unit_module->GetUnit(i);
    int new_obj_id = object_module->AddUnit(object);
    unit_module->GetUnitPtr(object.GetID())->SetID(new_obj_id);
  }
  
  for(int i = 0; i < projectile_module->GetSize(); i++) {
    CObject object = projectile_module->GetUnit(i);
    int new_obj_id = object_module->AddUnit(object);
    projectile_module->GetUnitPtr(object.GetID())->SetID(new_obj_id);
  }  
  
  object_render = new CObjectRender(object_module);
  unit_render = new CUnitRender(unit_module);
  projectile_render = new CProjectileRender(projectile_module);
    
  map = new CMap(&data_manager);
  map_render = new CMapRender(&rectDisplay, map, tile_render, unit_render, object_render, projectile_render);
  
  object_builder = new CObjectBuilder(map, map_render);
    
  map->Load("data/maps/mapa1.map");
  player_manager.AddPlayer("Drow", "");
  player_manager.AddPlayer("Snake", "");
  map->SetPlayerManager(&player_manager);
  
  object_builder->AddUnit(5, 5, 1, 0);
  object_builder->AddUnit(7, 4, 2, 0);
  object_builder->AddUnit(10, 9, 3, 0);
  object_builder->AddUnit(3, 7, 4, 0);
  object_builder->AddUnit(4, 12, 6, 0);

  object_builder->AddUnit(15, 8, 5, 1);
  object_builder->AddUnit(17, 4, 5, 1);
  object_builder->AddUnit(17, 10, 7, 1);
  
  map_controls = new CMapControls(map_render);
  unit_controls = new CUnitControls(map, map_render, object_builder, gui_manager);
  unit_controls->SetCurrentPlayerID(0);
  unit_controls->SetModifierModule(modifier_module);
  projectile_controls = new CProjectileControls(map, map_render, object_builder);
  
  game_controls = new CGameControls(&player_manager, unit_controls);

  return 0;
}

void CGame::OnEvent(SDL_Event* event)
{
  map_controls->OnEvent(event);
  unit_controls->OnEvent(event);
  game_controls->OnEvent(event);  
}

void CGame::OnRender()
{
  map_render->OnRender(surfDisplay);
  
  SDL_Rect   player_rect = {0, 0, 200, 32};
  SDL_Color  player_color = {255, 255, 255}; 
  
  font_render->RenderText(surfDisplay, player_rect, player_manager.GetPlayer(game_controls->GetCurrentPlayerID())->GetName(), player_color);  
}

void CGame::OnLoop()
{
  map_controls->OnLoop();
  unit_controls->OnLoop();
  projectile_controls->OnLoop();  
}

