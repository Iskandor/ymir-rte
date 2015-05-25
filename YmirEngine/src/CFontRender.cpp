/* 
 * File:   CFontRender.cpp
 * Author: Matej Pechac
 * 
 * Created on September 10, 2014, 9:29 PM
 */

#include "CFontRender.h"
#include <iostream>

CFontRender::CFontRender() {
  font = NULL;
}

CFontRender::CFontRender(const CFontRender& orig) {
  font = orig.font;
}

CFontRender::~CFontRender() {
  for(map<string, SDL_Surface*>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
    SDL_FreeSurface(pair<string, SDL_Surface*>(*it).second);
  }
}

int CFontRender::onInit()
{
  if (!LoadFonts()) {
    cout << "Error in loading fonts! " << TTF_GetError() << endl;
    return -1;
  }
  
  return 0;
}

void CFontRender::onCleanup()
{
  if (font != NULL)
  {
    TTF_CloseFont(font);
  }  
}

bool CFontRender::LoadFonts() {
  font = TTF_OpenFont( "data/fonts/UnZialish.ttf", 28 );
  if( font == NULL ) {
    return false;
  }
  return true;
}

void CFontRender::RenderText(SDL_Surface* dest, SDL_Rect dest_rect, string message, SDL_Color color) {
  SDL_Surface* message_surf = NULL;
  map<string, SDL_Surface*>::iterator it = dictionary.find(message);
  
  if (it == dictionary.end()) {
    message_surf = TTF_RenderText_Solid( font, message.c_str(), color );
    dictionary[message] = message_surf;
  }
  else {
    message_surf = pair<string, SDL_Surface*>(*it).second;
  }
  
  SDL_BlitSurface(message_surf, NULL, dest, &dest_rect);
}


