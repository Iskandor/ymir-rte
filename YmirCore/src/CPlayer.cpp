/* 
 * File:   CPlayer.cpp
 * Author: Matej Pechac
 * 
 * Created on May 30, 2014, 10:48 PM
 */

#include "CPlayer.h"

CPlayer::CPlayer() {
  name = "";
}

CPlayer::CPlayer(string name) {
  this->name = name;
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

CUnitEntity* CPlayer::GetUnit(int id) {
  return unit_tree[id];  
}
