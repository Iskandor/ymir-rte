/* 
 * File:   COverTextManager.cpp
 * Author: Matej Pechac
 * 
 * Created on April 15, 2015, 10:02 PM
 */

#include "CGuiElementManager.h"
#include "COverText.h"

CGuiElementManager::CGuiElementManager() : IManager<CGuiElement> () {
  overtext_font = TTF_OpenFont( "data/fonts/UnZialish.ttf", 12 );
}

CGuiElementManager::CGuiElementManager(const CGuiElementManager& orig) : IManager<CGuiElement> (orig) {
  overtext_font = orig.overtext_font;
}

CGuiElementManager::~CGuiElementManager() {
}

CGuiElement* CGuiElementManager::Add(SDL_Surface* dest, SDL_Rect position)
{
  CGuiElement* element = new CGuiElement(dest, position.x, position.y);
  
  entity_list.push_back(element);
  
  return element;
}

CGuiElement* CGuiElementManager::AddOverText(SDL_Surface* dest, SDL_Rect position, string text, SDL_Color color)
{
  CGuiElement* over_text = NULL;
  
  over_text = new COverText(dest, overtext_font, position, text, color);  
  entity_list.push_back(reinterpret_cast<COverText*>(over_text));
  
  return over_text;
}

