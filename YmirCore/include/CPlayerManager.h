/* 
 * File:   CPlayerManager.h
 * Author: Matej Pechac
 *
 * Created on June 5, 2014, 9:34 PM
 */

#ifndef CPLAYERMANAGER_H
#define	CPLAYERMANAGER_H

#include <map>

#include "CPlayer.h"

using namespace std;

class CPlayerManager {
public:
  CPlayerManager();
  CPlayerManager(const CPlayerManager& orig);
  virtual ~CPlayerManager();
  
  void AddPlayer(string name, string avatar);
  void RemovePlayer(int id);
  CPlayer* GetPlayer(int id);
  int   GetNextPlayerID(int id);
  int   GetPlayerCount();
  
private:
  int new_id;
  map<int, CPlayer> player_tree;
};

#endif	/* CPLAYERMANAGER_H */

