/* 
 * File:   CGuiElement.h
 * Author: Matej Pechac
 *
 * Created on April 21, 2015, 9:42 PM
 */

#ifndef CGUIELEMENT_H
#define	CGUIELEMENT_H

#include <SDL/SDL.h>

class CGuiElement {
public:
  CGuiElement(SDL_Surface* dest, int x, int y);
  CGuiElement(const CGuiElement& orig);
  virtual ~CGuiElement();
  
  void  OnRender();
  virtual void  OnLoop() {};
  
  bool  IsDestroied() { return destroy; };
  
protected:
  SDL_Surface*  dest;
  SDL_Surface*  surface;
  SDL_Rect      position_rect;
  
  bool          destroy;

};

#endif	/* CGUIELEMENT_H */

