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
  game = NULL;
  gui_manager = NULL;

  running = true;
}

CApp::CApp(const CApp& orig) {
  running = orig.running;
}

CApp::~CApp() {
  if (surfDisplay != NULL)
  {
    SDL_FreeSurface(surfDisplay);
  }
  
  if (gui_manager != NULL)
  {
    //delete gui_manager;
  }
  
  if (game != NULL)
  {
    delete game;
  }

}

int CApp::OnExecute() {
  SDL_Event event;

  if (OnInit() != 0) {
    return -1;
  }
  
  FPS = 32;
  
  Uint32  start;

  while(running) {
    start = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }
    OnLoop();
    OnRender();

    if (1000/FPS < (SDL_GetTicks() - start))
    {
      FPS--;
    }
    if (1000/FPS > (SDL_GetTicks() - start)) {
      SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
      FPS++;
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

  rectDisplay.x = rectDisplay.y = 0;
  rectDisplay.w = RESOLUTION_W;
  rectDisplay.h = RESOLUTION_H;
  
  if ((surfDisplay = SDL_SetVideoMode(rectDisplay.w, rectDisplay.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) { /*SDL_FULLSCREEN*/
    return -2;
  }
  
  if (font_render.onInit() != 0)
  {
    return -3;
  }
  
  gui_manager = new CGuiManager(surfDisplay, &font_render);
  if (gui_manager->OnInit() != 0) {
    return -4;
  }
  
  game = new CGame(surfDisplay, rectDisplay, gui_manager, &font_render);
  if (game->OnInit() != 0)
  {
    return -5;
  }
  
  return 0;
}

void CApp::OnLoop() {
  game->OnLoop();
  gui_manager->OnLoop();
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

  game->OnEvent(event);
  gui_manager->OnEvent(*event);
}

void CApp::OnRender() {
  SDL_FillRect(surfDisplay, NULL, SDL_MapRGB(surfDisplay->format, 0, 0, 0));
  
  game->OnRender();
  gui_manager->OnRender();
  
  //font_render->RenderText(surfDisplay, {0, 32, 200, 32}, to_string(FPS), player_color);
  
  SDL_Flip(surfDisplay);
}

void CApp::OnCleanup() {
  font_render.onCleanup();
  SDL_Quit();
  TTF_Quit();
}


