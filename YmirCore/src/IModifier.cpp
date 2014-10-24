/* 
 * File:   IModifier.cpp
 * Author: Matej Pechac
 *
 * Created on September 24, 2014, 9:24 PM
 */

#include "IModifier.h"

IModifier::IModifier() {
  this->mod_class = E_MODIFIER::HURT;
  this->id = -1;
  this->duration = 0;  
}

IModifier::IModifier(E_MODIFIER mod_class, int id, int duration, string desc) {
  this->mod_class = mod_class;
  this->id = id;
  this->duration = duration;
  this->desc = desc;
}

IModifier::IModifier(E_MODIFIER mod_class, int id, int duration, string desc, int delta, int per) {
  this->mod_class = mod_class;
  this->id = id;
  this->duration = duration;
  this->desc = desc;  
  
  switch(this->mod_class) {
    case HURT:
    case BLEED:
    case HEAL:
      delta_hp = delta;
      per_hp = per;
      break;
    case PARALYZE:
    case BREAK:
      delta_st = delta;
      per_st = per;
      break;
    default:
      break;
  }  
}

IModifier::IModifier(map<string,string> data) {
  mod_class = (E_MODIFIER)stoi(data["mod_class"]);
  id = stoi(data["id"]);
  duration = stoi(data["duration"]);
  desc = data["desc"];
  
  delta_hp = stoi(data["delta_hp"]);
  per_hp = stoi(data["per_hp"]);
  delta_st = stoi(data["delta_st"]);
  per_st = stoi(data["per_st"]);
}

IModifier::IModifier(const IModifier& orig) {
  mod_class = orig.mod_class;
  id = orig.id;
  duration = orig.duration;
  desc = orig.desc;  
 
  delta_hp = orig.delta_hp;
  per_hp = orig.per_hp;
  delta_st = orig.delta_st;
  per_st = orig.per_st;
}

IModifier::~IModifier() {
}

map<string, string> IModifier::exportMap() {
  map<string, string> result;
  
  result["mod_class"] = to_string(mod_class);
  result["id"] = to_string(id);
  result["duration"] = to_string(duration);
  result["desc"] = desc;
  
  result["delta_hp"] = to_string(delta_hp);
  result["per_hp"] = to_string(per_hp);
  result["delta_st"] = to_string(delta_st);
  result["per_st"] = to_string(per_st);  
  
  return result;
}

void IModifier::Apply() {
  
}
