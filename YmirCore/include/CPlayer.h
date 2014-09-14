/* 
 * File:   CPlayer.h
 * Author: Matej Pechac
 *
 * Created on May 30, 2014, 10:48 PM
 */

#ifndef CPLAYER_H
#define	CPLAYER_H

#include <string>
#include <map>
#include <CUnitEntity.h>

using namespace std;

class CPlayer { 
  
public:
  
  enum E_RELATION {
    ALLY,
    ENEMY
  };
  
  CPlayer();
  CPlayer(int id, string name, string avatar);
  CPlayer(const CPlayer& orig);
  virtual ~CPlayer();
private:
  int     id;
  string  name;
  string  avatar;
  map<int, CUnitEntity*> unit_tree;
  vector<pair<int, E_RELATION> > diplomacy;
  
public:
  void    SetName(string name) { this->name = name; };
  string  GetName() { return name; };
  
  void    SetAvatar(string avatar) { this->avatar = avatar; };
  string  GetAvatar() { return avatar; };

  int GetID() { return id; };
  
  void  AddUnit(CUnitEntity* unit_entity);
  void  RemoveUnit(int id);
  CUnitEntity* GetUnit(int id);
  void  RestoreUnitSP();
};

#endif	/* CPLAYER_H */

