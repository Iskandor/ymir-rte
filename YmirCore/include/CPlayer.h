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
  CPlayer();
  CPlayer(string name);
  CPlayer(const CPlayer& orig);
  virtual ~CPlayer();
private:
  string  name;
  map<int, CUnitEntity*> unit_tree;
  
public:
  void SetName(string name) { this->name = name; };
  string GetName() { return name; };
  
  void AddUnit(CUnitEntity* unit_entity);
  CUnitEntity* GetUnit(int id);
};

#endif	/* CPLAYER_H */

