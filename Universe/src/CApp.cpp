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

  while(running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }
    OnLoop();
    OnRender();
  }

  OnCleanup();

  return 0;
}

int CApp::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return -1;
  }
  
  rectDisplay.x = rectDisplay.y = 0;
  rectDisplay.w = 1280;
  rectDisplay.h = 720;
  
  if ((surfDisplay = SDL_SetVideoMode(rectDisplay.w, rectDisplay.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) { /*SDL_FULLSCREEN*/
    return -2;
  }
  
  tile_module.LoadFromXML("data/tiles", "tiles", "tile");
  tile_render = new CTileRender(&tile_module);
  
  object_module.LoadFromXML("data/objects", "objects", "object"); 
  unit_module.LoadFromXML("data/units", "units", "unit");
  
  for(int i = 0; i < unit_module.GetSize(); i++) {
    CObject object = unit_module.GetUnit(i);
    object_module.AddUnit(object);
  }
  
  object_render = new CObjectRender(&object_module);  
  unit_render = new CUnitRender(&unit_module);
    
  map = new CMap(&tile_module, &unit_module, &object_module);
  map->Load("data/maps/mapa1.map");
  map->addUnit(5, 5, 1);
  map->addUnit(7, 4, 2);
  map->addUnit(10, 9, 3);
  map->addUnit(3, 7, 4);
  
  map_render = new CMapRender(&rectDisplay, map, tile_render, unit_render, object_render);
  map_controls = new CMapControls(map_render);
  unit_controls = new CUnitControls(map_render);
  
  return 0;
}

void CApp::OnLoop() {
  map_controls->OnLoop();
  unit_controls->OnLoop();
  SDL_Delay(1000 / 32);
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
}

void CApp::OnRender() {
  SDL_FillRect(surfDisplay, NULL, SDL_MapRGB(surfDisplay->format, 0, 0, 0));
  map_render->OnRender(surfDisplay);
  SDL_Flip(surfDisplay);
}

void CApp::OnCleanup() {
  SDL_Quit();
}


