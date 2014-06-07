/* 
 * File:   CPlayerManager.cpp
 * Author: Matej Pechac
 * 
 * Created on June 5, 2014, 9:34 PM
 */

#include <assert.h>
#include "CPlayerManager.h"

CPlayerManager::CPlayerManager() {
  new_id = 0;
  player_tree.clear();
}

CPlayerManager::CPlayerManager(const CPlayerManager& orig) {
  new_id = orig.new_id;
  player_tree = orig.player_tree;
}

CPlayerManager::~CPlayerManager() {
}

void CPlayerManager::AddPlayer(string name, string avatar) {
  player_tree[new_id] = CPlayer(new_id, name, avatar);
  new_id++;
}

void CPlayerManager::RemovePlayer(int id) {
  player_tree.erase(id);
}

CPlayer* CPlayerManager::GetPlayer(int id) {
  return &(player_tree[id]);
}

int CPlayerManager::GetNextPlayerID(int id) {
  map<int, CPlayer>::iterator it;
  
  for(it = player_tree.begin(); it != player_tree.end(); it++) {
    if (it->second.GetID() == id) {
      it++;
      if (it != player_tree.end()) {
        return it->second.GetID();
      }
      else {
        it = player_tree.begin();
        return -it->second.GetID();
      }
    }
  }
  assert(0);
  return 0;
}

int CPlayerManager::GetPlayerCount() {
  return player_tree.size();
}

