/* 
 * File:   CModifier.h
 * Author: Matej Pechac
 *
 * Created on September 19, 2014, 11:15 PM
 */

#ifndef CMODIFIER_H
#define	CMODIFIER_H

#include "CUnitEntity.h"
#include "IModifier.h"


using namespace std;

class CModifier : public IModifier {
public:
  CModifier();
  CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration, string desc);
  CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration, string desc, int delta, int per);
  CModifier(map<string, string> data);
  CModifier(const CModifier& orig);
  virtual ~CModifier();
    
  bool Apply();
  void SetUnitEntity(CUnitEntity* value) { unit_entity = value; };
  
  CUnitEntity* GetUnitEntity() { return unit_entity; };
  
private:
  void Hurt();
  void Heal();
  void Paralyze();
  
private:
  CUnitEntity*  unit_entity;  
};

#endif	/* CMODIFIER_H */

