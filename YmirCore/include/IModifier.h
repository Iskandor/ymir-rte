/* 
 * File:   IModifier.h
 * Author: Matej Pechac
 *
 * Created on September 24, 2014, 9:24 PM
 */

#ifndef IMODIFIER_H
#define	IMODIFIER_H

#include <map>
#include <string>
#include "ISerializable.h"

using namespace std;

class IModifier : public ISerializable {
public:
  enum E_MODIFIER {
    HURT = 0,
    BLEED = 1,
    BREAK = 2,
    HEAL = 3,
    PARALYZE = 4
  };
  
  enum E_RESOLVE {
    INSTANT = 0,
    END_TURN = 1
  };

  IModifier();
  IModifier(E_MODIFIER mod_class, int id, int duration, string desc);
  IModifier(E_MODIFIER mod_class, int id, int duration, string desc, int delta, int per);
  IModifier(map<string, string> data);
  IModifier(const IModifier& orig);
  virtual ~IModifier();

  map<string, string> exportMap();
  int GetID() { return id; };
  void SetID(int value) { id = value; };
  int GetTypeID() { return id; };
  int GetDuration() { return duration; };
  void SetDuration(int value) { duration = value; };
  string GetDesc() { return desc; };
  void SetDesc(string value) { desc = value; };
  E_MODIFIER GetClass() { return mod_class; }
  void SetClass(E_MODIFIER value) { mod_class = value; };
  
  int GetDeltaHP() { return delta_hp; };
  void SetDeltaHP(int value) { delta_hp = value; };
  int GetPerHP() { return per_hp; };
  void SetPerHP(int value) { per_hp = value; };
  int GetDeltaST() { return delta_st; };
  void SetDeltaST(int value) { delta_st = value; };
  int GetPerST() { return per_st; };
  void SetPerST(int value) { per_st = value; };  
  
  virtual void Apply();
  
protected:
  int           id;
  E_MODIFIER    mod_class;

  int     duration;
  string  desc;
  
  int delta_hp;
  int per_hp;
  int delta_st;
  int per_st;
};

#endif	/* IMODIFIER_H */

