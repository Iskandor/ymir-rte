/* 
 * File:   CMapControls.cpp
 * Author: Matej Pechac
 * 
 * Created on April 8, 2014, 7:50 PM
 */

#include "CMapControls.h"
#include "GlobalDefine.h"

CMapControls::CMapControls(CMapRender* map_render) {
  this->map_render = map_render;
  
  scrolling = false;
  scroll_direction.first = 0;
  scroll_direction.second = 0;
}

CMapControls::CMapControls(const CMapControls& orig) {
}

CMapControls::~CMapControls() {
}

void CMapControls::OnEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_KEYUP: {    
    } break;
    case SDL_MOUSEMOTION: {
     
      if (event->motion.x < 5) {
        scrolling = true;
        scroll_direction.first = -1;
      } 
      else if (event->motion.x > (map_render->GetMainRect()->w - 5)) {
        scrolling = true;
        scroll_direction.first = 1;
      }
      else if (event->motion.y < 5) {
        scrolling = true;
        scroll_direction.second = -1;
      } 
      else if (event->motion.y > (map_render->GetMainRect()->h - 5)) {
        scrolling = true;
        scroll_direction.second = 1;
      }
      else {
        scroll_direction.first = 0;
        scroll_direction.second = 0;        
        scrolling = false;
      }      
    } break;
  }
}

void CMapControls::OnLoop() {
  if (scrolling) {
    if (scroll_direction.first < 0) {
      if (map_render->GetCamera()->x > 0) {
        map_render->GetCamera()->x--;
      }
    }
    if (scroll_direction.first > 0) {
      if (map_render->GetCamera()->x + map_render->GetCamera()->w < map_render->GetMap()->getMapSizeX(sizemode_elem)) {
        map_render->GetCamera()->x++;
      }
    } 
    if (scroll_direction.second < 0) {
      if (map_render->GetCamera()->y > 0) {
        map_render->GetCamera()->y--;
      }
    }
    if (scroll_direction.second > 0) {
      if (map_render->GetCamera()->y + map_render->GetCamera()->h < map_render->GetMap()->getMapSizeY(sizemode_elem)) {
        map_render->GetCamera()->y++;
      }
    }    
  }
}

