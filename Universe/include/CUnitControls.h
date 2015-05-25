/* 
 * File:   CUnitControls.h
 * Author: Matej Pechac
 *
 * Created on April 12, 2014, 10:23 AM
 */

#ifndef CUNITCONTROLS_H
#define	CUNITCONTROLS_H

#include <SDL/SDL.h>

#include "CMap.h"
#include "CMapRender.h"
#include "CUnitEntity.h"
#include "CModifier.h"
#include "CGuiManager.h"
#include "CControls.h"

class CUnitControls : public CControls {
public:
  CUnitControls(CMap* map, CMapRender* map_render, CObjectBuilder* object_builder, CGuiManager* gui_manager);
  CUnitControls(const CUnitControls& orig);
  virtual ~CUnitControls();
  
  void OnEvent(SDL_Event* event);
  void OnLoop();
  
  void SetCurrentPlayerID(int value) { current_player_id = value; };
  void SetModifierModule(CModule<CModifier>* value) { modifier_module = value; };
  void ResolveModifiers();
  void DeselectUnit();
  
private:
  bool PerformAction(CUnitEntity* unit_entity, CAction* action);
  bool CanPerformAction(CUnitEntity* unit_entity, CAction* action, double tmp_sp = -1);
  bool CreatePath(CUnitEntity* unit_entity, CAction* action);
  bool CreatePath(CUnitEntity* unit_entity, int x, int y, double* sp = NULL);
  void Move(CUnitEntity* unit_entity, CAction* action);
  void Attack(CUnitEntity* unit_entity, CAction* action);
  void FireOrFight(CUnitEntity* unit_entity, CUnitEntity* target);
  void Fight(CUnitEntity* unit_entity, CUnitEntity* target, bool recursive = true);
  void Die(CUnitEntity* unit_entity);
  void Turn(CUnitEntity* unit_entity, int x);
  
  void ResolveModifier(CUnitEntity* unit_entity);
  void RemoveAttackOnDead(CUnitEntity* dead);
  
  pair<int, int>          GetAttackPosition(CUnitEntity* attacker, CUnitEntity* target);
  queue< pair<int, int> > GeneratePath(CUnitEntity* unit_entity, int x, int y);
  queue< pair<int, int> > ReconstructPath(int* came_from, int length, int current_node, int size_x);
  
  
private:
  CGuiManager*  gui_manager;
  
  CModule<CModifier>* modifier_module;
  
  CUnitEntity*  selected_unit;
  int           current_player_id;
};

#endif	/* CUNITCONTROLS_H */

