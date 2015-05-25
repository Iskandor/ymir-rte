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
#include "CGuiManager.h"
#include "CFontRender.h"
#include "CGame.h"

class CApp {
public:
  CApp();
  CApp(const CApp& orig);
  virtual ~CApp();

private:
  CFontRender     font_render;
  CGuiManager     *gui_manager;
  CGame           *game;
  
  bool  running;
  int   FPS;

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

