/* 
 * File:   COverText.h
 * Author: Matej Pechac
 *
 * Created on April 15, 2015, 9:37 PM
 */

#ifndef COVERTEXT_H
#define	COVERTEXT_H

#include <SDL/SDL_ttf.h>
#include <string>

#include "CGuiElement.h"

using namespace std;

class COverText : public CGuiElement {
public:
  const int MAX_STEP = 25;
  
  COverText(SDL_Surface* dest, TTF_Font *font, SDL_Rect position, string text, SDL_Color color);
  COverText(const COverText& orig);
  virtual ~COverText();

  void  OnLoop();
  
  int GetStep() { return step; };
  
private:
  TTF_Font      *font;
  
  SDL_Color     color;
  
  string        message;
  int           alpha_value;
  int           step;
  
};

#endif	/* COVERTEXT_H */

