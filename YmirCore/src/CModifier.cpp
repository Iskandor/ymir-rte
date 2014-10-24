/* 
 * File:   CModifier.cpp
 * Author: Matej Pechac
 * 
 * Created on September 19, 2014, 11:15 PM
 */

#include "CModifier.h"

CModifier::CModifier() : IModifier() {
  this->unit_entity = NULL;
}

CModifier::CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration, string desc) : IModifier(mod_class, id, duration, desc) {
  this->unit_entity = unit_entity;
}

CModifier::CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration, string desc, int delta, int per) : IModifier(mod_class, id, duration, desc, delta, per) {
  this->unit_entity = unit_entity;
}

CModifier::CModifier(const CModifier& orig) : IModifier(orig) {
  unit_entity = orig.unit_entity;
}

CModifier::CModifier(map<string,string> data) : IModifier(data) {
  
}

CModifier::~CModifier() {
}

void CModifier::Apply() {
  if (duration == 0) {
    return;
  }
  
  duration--;
  
  switch(this->mod_class) {
    case HURT:
    case BLEED:
      Hurt();
      break;
    case HEAL:
      Heal();
      break;
    case PARALYZE:
      Paralyze();
      break;
    case BREAK:
      break;
    default:
      break;
  }  
}

void CModifier::Hurt() {
  if (delta_hp > 0) {
    if (delta_hp >= unit_entity->GetHP()) {
      unit_entity->SetHP(0);
      unit_entity->AddAction(CAction(CAction::DIE, 0));
    }
    else {
      int new_hp = unit_entity->GetHP() - delta_hp;
      unit_entity->SetHP(new_hp);
    }
  }
}

void CModifier::Heal() {
  
}

void CModifier::Paralyze() {
  if (delta_st > 0) {
    if (delta_st >= unit_entity->GetSP()) {
      unit_entity->SetSP(0);
    }
    else {
      unit_entity->DecreaseSP(delta_st);
    }
  }
  if (per_st > 0) {
    double delta = per_st/100 * unit_entity->GetMaxSP();
    if (delta >= unit_entity->GetSP()) {
      unit_entity->SetSP(0);
    }
    else {
      unit_entity->DecreaseSP(delta);
    }    
  }
}
