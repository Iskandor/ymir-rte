/* 
 * File:   CGameControls.cpp
 * Author: Matej Pechac
 * 
 * Created on June 5, 2014, 10:17 PM
 */

#include "CGameControls.h"

CGameControls::CGameControls(CPlayerManager* player_manager) {
  this->player_manager = player_manager;
  current_player_id = 0;
  turn = 0;
}

CGameControls::CGameControls(const CGameControls& orig) {
  player_manager = orig.player_manager;
  current_player_id = orig.current_player_id;
  turn = orig.turn;
}

CGameControls::~CGameControls() {
}

void CGameControls::OnEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_KEYUP: { 
      if (event->key.keysym.sym == SDLK_t) {
        NextPlayer();
      }
    } break;
  }
}

void CGameControls::OnLoop() {
  
}

void CGameControls::NextPlayer() {
  current_player_id = player_manager->GetNextPlayerID(current_player_id);
  if (current_player_id < 0) {
    current_player_id = -current_player_id;
    turn++;
  }
}

