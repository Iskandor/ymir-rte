/* 
 * File:   COverText.cpp
 * Author: Matej Pechac
 * 
 * Created on April 15, 2015, 9:37 PM
 */

#include "COverText.h"

COverText::COverText(SDL_Surface* dest, TTF_Font *font, SDL_Rect position, string text, SDL_Color color) : CGuiElement(dest, position.x, position.y) {
  this->font = font;
  this->color = color;
  message = text;
  surface = TTF_RenderText_Solid( font, message.c_str(), color );
  
  
  position_rect.x = position.x + (position.w - surface->w) / 2;
  position_rect.y = position.y;
  position_rect.w = surface->w;
  position_rect.h = surface->h;
  
  alpha_value = 255;
  step = 0;
}

COverText::COverText(const COverText& orig) : CGuiElement(orig) {
  font = orig.font;
  color = orig.color;
  message = orig.message;
}

COverText::~COverText() {
}

void COverText::OnLoop()
{ 
  if (step < MAX_STEP)
  {
    position_rect.y-=2;
    alpha_value -= 10;

    SDL_SetAlpha(surface, SDL_SRCALPHA, alpha_value);
    surface = SDL_DisplayFormat(surface);

    step++;
  }
  else
  {
    destroy = true;
  }
}

