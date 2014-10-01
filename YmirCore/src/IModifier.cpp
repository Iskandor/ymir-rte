/* 
 * File:   IModifier.cpp
 * Author: Matej Pechac
 *
 * Created on September 24, 2014, 9:24 PM
 */

#include "IModifier.h"


IModifier::IModifier(E_MODIFIER mod_class, int id, int duration) {
  this->mod_class = mod_class;
  this->id = id;
  this->duration = duration;
}

IModifier::IModifier(E_MODIFIER mod_class, int id, int duration, int delta, int per) {
  this->mod_class = mod_class;
  this->id = id;
  this->duration = duration;
  
  switch(this->mod_class) {
    case HURT:
    case BLEED:
    case HEAL:
      delta_hp = delta;
      per_hp = per;
      break;
    case PARALYZE:
    case BREAK:
      break;
    default:
      break;
  }  
}


IModifier::IModifier(const IModifier& orig) {
  mod_class = orig.mod_class;
  id = orig.id;
  duration = orig.duration;
 
  delta_hp = orig.delta_hp;
  per_hp = orig.per_hp;  
}

IModifier::~IModifier() {
}

map<string, string> IModifier::exportMap() {
  map<string, string> result;
  
  
  return result;
}

void IModifier::Apply() {
  
}
