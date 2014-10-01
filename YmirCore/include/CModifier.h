/* 
 * File:   CModifier.h
 * Author: Matej Pechac
 *
 * Created on September 19, 2014, 11:15 PM
 */

#ifndef CMODIFIER_H
#define	CMODIFIER_H

#include <map>
#include <string>

#include "CUnitEntity.h"
#include "IModifier.h"


using namespace std;

class CModifier : public IModifier {
public:
  CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration);
  CModifier(E_MODIFIER mod_class, int id, CUnitEntity* unit_entity, int duration, int delta, int per);
  CModifier(map<string, string> data);
  CModifier(const CModifier& orig);
  virtual ~CModifier();
    
  void Apply();
  
private:
  void Hurt();
  void Heal();
  void Paralyze();
  
private:
  CUnitEntity*  unit_entity;  
};

#endif	/* CMODIFIER_H */

