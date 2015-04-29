/* 
 * File:   CGuiElementManager.h
 * Author: Matej Pechac
 *
 * Created on April 15, 2015, 10:02 PM
 */

#ifndef COVERTEXTMANAGER_H
#define	COVERTEXTMANAGER_H

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "CGuiElement.h"
#include "IManager.h"

using namespace std;

class CGuiElementManager : public IManager<CGuiElement> {
public:
  CGuiElementManager();
  CGuiElementManager(const CGuiElementManager& orig);
  virtual ~CGuiElementManager();
  
  CGuiElement* AddOverText(SDL_Surface* dest, SDL_Rect position, string text, SDL_Color color);
  CGuiElement* Add(SDL_Surface* dest, SDL_Rect position);
  
private:
  TTF_Font *overtext_font;
};

#endif	/* COVERTEXTMANAGER_H */

