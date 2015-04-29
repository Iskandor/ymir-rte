/* 
 * File:   CGuiManager.h
 * Author: Matej Pechac
 *
 * Created on June 7, 2014, 4:29 PM
 */

#ifndef CGUIMANAGER_H
#define	CGUIMANAGER_H

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <SDL/SDL.h>
#include <string>
#include <vector>

#include <QtCore/QXmlStreamWriter>
#include <QtCore/QFile>

#include "CFontRender.h"
#include "GlobalDefine.h"
#include "CUnitEntity.h"
#include "CGuiElementManager.h"

using namespace gcn;
using namespace std;

class CGuiManager {
public:
  CGuiManager(SDL_Surface* surface, CFontRender* font_render);
  CGuiManager(const CGuiManager& orig);
  virtual ~CGuiManager();
  
  int   OnInit();
  void  OnRender();
  void  OnEvent(SDL_Event event);
  void  OnLoop();
  
  void  OnUnitClick(CUnitEntity* unit_entity);
  
  CGuiElementManager* GuiElementManager() { return &gui_element_manager;};
  SDL_Surface* Screen() { return screen; };
private:
  
private:
  CGuiElementManager  gui_element_manager;
  
  SDL_Surface*    screen;
  SDLInput*       input;
  SDLGraphics*    graphics;
  SDLImageLoader* imageLoader;
  
  
  Gui*        gui;
  ImageFont*  font;
  
  /* containers */
  Container*  top;
  Container*  unit_info;
  
  Label*      lb_hp;
  Label*      lb_st;
  Label*      lbv_unit_class;
  Label*      lbv_race;
  Label*      lbv_hp;
  Label*      lbv_st;
  
  CFontRender* font_render;
};

#endif	/* CGUIMANAGER_H */

