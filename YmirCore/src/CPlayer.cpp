/* 
 * File:   CPlayer.cpp
 * Author: Matej Pechac
 * 
 * Created on May 30, 2014, 10:48 PM
 */

#include "CPlayer.h"

CPlayer::CPlayer() {
  id = 0;
  name = "";
  avatar = "";
}

CPlayer::CPlayer(int player_id, string name, string avatar) {
  this->id = player_id;
  this->name = name;
  this->avatar = avatar;
}

CPlayer::CPlayer(const CPlayer& orig) {
  name = orig.name;
  unit_tree = orig.unit_tree;
}

CPlayer::~CPlayer() {
}

void CPlayer::AddUnit(CUnitEntity* unit_entity) {
  unit_tree[unit_entity->GetID()] = unit_entity;
}

void CPlayer::RemoveUnit(int id) {
  unit_tree.erase(id);
}

CUnitEntity* CPlayer::GetUnit(int id) {
  return unit_tree[id];  
}
