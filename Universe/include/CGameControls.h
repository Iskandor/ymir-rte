/* 
 * File:   CGameControls.h
 * Author: Matej Pechac
 *
 * Created on June 5, 2014, 10:17 PM
 */

#ifndef CGAMECONTROLS_H
#define	CGAMECONTROLS_H

#include <SDL/SDL.h>
#include "CPlayerManager.h"


class CGameControls {
public:
  CGameControls(CPlayerManager* player_manager);
  CGameControls(const CGameControls& orig);
  virtual ~CGameControls();
  
  void OnEvent(SDL_Event* event);
  void OnLoop();
  
private:
  CPlayerManager* player_manager;
  int current_player_id;
  int turn;
  
  void NextPlayer();
};

#endif	/* CGAMECONTROLS_H */

