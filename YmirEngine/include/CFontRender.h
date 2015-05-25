/* 
 * File:   CFontRender.h
 * Author: Matej Pechac
 *
 * Created on September 10, 2014, 9:29 PM
 */

#ifndef CFONTRENDER_H
#define	CFONTRENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <map>

using namespace std;

class CFontRender {
public:
  CFontRender();
  CFontRender(const CFontRender& orig);
  virtual ~CFontRender();
  
  int onInit();
  void onCleanup();
  
  bool  LoadFonts();
  void  RenderText(SDL_Surface* dest, SDL_Rect dest_rect, string message, SDL_Color color);
private:
  TTF_Font *font = NULL;
  
  map<string, SDL_Surface*> dictionary;
};

#endif	/* CFONTRENDER_H */

