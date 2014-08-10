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

using namespace gcn;
using namespace std;

class CGuiManager {
public:
  CGuiManager(SDL_Surface* surface);
  CGuiManager(const CGuiManager& orig);
  virtual ~CGuiManager();
  
  int   OnInit();
  void  OnRender();
  
private:
  int   LoadXML(string filename);
  
private:
  SDL_Surface*    screen;
  SDLInput*       input;
  SDLGraphics*    graphics;
  SDLImageLoader* imageLoader;
  vector<Gui*>    gui;
  Container*  top;
  ImageFont*  font;
  Label*      label;
};

#endif	/* CGUIMANAGER_H */

