/* 
 * File:   CGuiElement.cpp
 * Author: Matej Pechac
 * 
 * Created on April 21, 2015, 9:42 PM
 */

#include "CGuiElement.h"

CGuiElement::CGuiElement(SDL_Surface* dest, int x, int y) {
  this->dest = dest;  
  position_rect.x = (Sint16)x;
  position_rect.y = (Sint16)y;
  destroy = false;
}

CGuiElement::CGuiElement(const CGuiElement& orig) {
  dest = orig.dest;
  position_rect = orig.position_rect;
  surface = orig.surface;
  destroy = orig.destroy;
}

CGuiElement::~CGuiElement() {
  if (surface != NULL)
  {
    SDL_FreeSurface(surface);
  }
  
}

void CGuiElement::OnRender()
{
  SDL_BlitSurface(surface, NULL, dest, &position_rect);
}

