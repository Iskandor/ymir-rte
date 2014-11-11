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

class CUnitControls {
public:
  CUnitControls(CMapRender* map_render, CGuiManager* gui_manager);
  CUnitControls(const CUnitControls& orig);
  virtual ~CUnitControls();
  
  void OnEvent(SDL_Event* event);
  void OnLoop();
  
  void SetCurrentPlayerID(int value) { current_player_id = value; };
  void SetModifierModule(CModule<CModifier>* value) { modifier_module = value; };
  void ResolveModifiers();
  
private:
  bool PerformAction(CUnitEntity* unit_entity, CAction* action);
  void CreatePath(CUnitEntity* unit_entity, CAction* action);
  void CreatePath(CUnitEntity* unit_entity, int x, int y);
  void Move(CUnitEntity* unit_entity, CAction* action);
  void Attack(CUnitEntity* unit_entity, CAction* action);
  void FireOrFight(CUnitEntity* unit_entity, CUnitEntity* target);
  void Fight(CUnitEntity* unit_entity, CUnitEntity* target);
  void Die(CUnitEntity* unit_entity);
  void ResolveModifier(CUnitEntity* unit_entity);
  
  pair<int, int>          GetAttackPosition(CUnitEntity* attacker, CUnitEntity* target);
  queue< pair<int, int> > GeneratePath(CUnitEntity* unit_entity, int x, int y);
  queue< pair<int, int> > ReconstructPath(int* came_from, int length, int current_node, int size_x);
  
  
private:
  CMapRender*   map_render;
  CMap*         map;
  CGuiManager*  gui_manager;
  
  CModule<CModifier>* modifier_module;
  
  CUnitEntity*  selected_unit;
  int           current_player_id;
};

#endif	/* CUNITCONTROLS_H */

