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

using namespace std;

class IModifier {
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

  IModifier(E_MODIFIER mod_class, int id, int duration);
  IModifier(E_MODIFIER mod_class, int id, int duration, int delta, int per);
  IModifier(const IModifier& orig);
  virtual ~IModifier();

  map<string, string> exportMap();
  int GetTypeID() { return id; };
  int GetDuration() { return duration; };
  
  virtual void Apply();
  
protected:
  int           id;
  E_MODIFIER    mod_class;

  int duration;
  
  int delta_hp;
  int per_hp;
};

#endif	/* IMODIFIER_H */

