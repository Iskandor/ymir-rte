/* 
 * File:   CModifier.cpp
 * Author: Matej Pechac
 * 
 * Created on September 19, 2014, 11:15 PM
 */

#include "CModifier.h"

CModifier::CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration) : IModifier(mod_class, id, duration) {
  this->unit_entity = unit_entity;
}

CModifier::CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration, int delta, int per) : IModifier(mod_class, id, duration, delta, per) {
  this->unit_entity = unit_entity;
}

CModifier::CModifier(const CModifier& orig) : IModifier(orig) {
  unit_entity = orig.unit_entity;
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
  if (delta_hp > -1) {
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
  
}
