/* 
 * File:   CUnitControls.cpp
 * Author: Matej Pechac
 * 
 * Created on April 12, 2014, 10:23 AM
 */

#include <CProjectileEntity.h>

#include "CUnitControls.h"
#include "CMapRender.h"
#include "GlobalDefine.h"
#include "CUtils.h"
#include "CMathUtils.h"
#include "CModifier.h"
#include "CObjectBuilder.h"

CUnitControls::CUnitControls(CMap* map, CMapRender* map_render, CObjectBuilder* object_builder, CGuiManager* gui_manager) : CControls(map, map_render, object_builder) {
  this->gui_manager = gui_manager;
  selected_unit = NULL;
}

CUnitControls::CUnitControls(const CUnitControls& orig) : CControls(orig) {
  current_player_id = orig.current_player_id;
  selected_unit = orig.selected_unit;
}

CUnitControls::~CUnitControls() {
}

void CUnitControls::OnEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_MOUSEBUTTONUP:
      if (event->button.button == SDL_BUTTON_LEFT) {
        CUnitEntity* unit_entity = NULL;
        SDL_Rect     unit_rect;
        SDL_Rect*    camera;
        int i = 0;
        
        for(i = 0; i < map->GetUnitManager()->GetListSize(); i++) {
          unit_entity = map->GetUnitManager()->Get(i);
          if (unit_entity->GetPlayerID() == current_player_id) {
            unit_rect.x = unit_entity->GetX();
            unit_rect.y = unit_entity->GetY();
            unit_rect.w = 4;
            unit_rect.h = 4;

            camera = map_render->GetCamera();

            pair<int, int> click;

            click.first = (event->button.x / MAP_ELEM) + camera->x;
            click.second = (event->button.y / MAP_ELEM) + camera->y;

            if (CUtils::PointIsInArea(click, unit_rect)) {
              DeselectUnit();
              
              CObjectEntity* selector = object_builder->AddObject(unit_entity->GetX()+(unit_entity->GetRootUnit()->GetXSize()-4), unit_entity->GetY()+(unit_entity->GetRootUnit()->GetYSize()-4), BOTTOM, 0);
              unit_entity->SetRefObject(selector);
              selected_unit = unit_entity;
              gui_manager->OnUnitClick(selected_unit);
              /*
              map->Unblock(selected_unit);
              selected_unit->OnClick(map->GetCostMap(), map->getMapSizeX(sizemode_elem), map->getMapSizeY(sizemode_elem));
              map->Block(selected_unit);
               * */
              break;
            }
          }
        }
        if (i == map->GetUnitManager()->GetListSize()) {
          DeselectUnit();
        }
      }
      if (event->button.button == SDL_BUTTON_RIGHT) {
        if (selected_unit != NULL) {
          SDL_Rect*    camera = map_render->GetCamera();
          int x = (event->button.x / MAP_ELEM) + camera->x;
          int y = (event->button.y / MAP_ELEM) + camera->y;
          CUnitEntity* other_unit = map->GetUnitManager()->Get(x, y);
          
          if (other_unit != NULL) {
            if (other_unit->GetPlayerID() != current_player_id) {              
              CAction action(CAction::ATTACK, other_unit, 1);
              if (CanPerformAction(selected_unit, &action))
              {
                selected_unit->AddAction(action);
              }
            }
          }
          else
          {
            x = (event->button.x / MAP_ELEM) + camera->x - (selected_unit->GetRootObject()->GetXSize() / 2);
            y = (event->button.y / MAP_ELEM) + camera->y - (selected_unit->GetRootObject()->GetYSize() - 1);
             
            selected_unit->AddAction(CAction(CAction::CREATE_PATH, x, y, 0));
          }
        }
      }
    break;
  }
}

void CUnitControls::OnLoop() {
  CUnitEntity*  unit_entity = NULL;
  CAction       action;
  
  for(int i = 0; i < map->GetUnitManager()->GetListSize(); i++) {
    unit_entity = map->GetUnitManager()->Get(i);
    action = unit_entity->GetAction(false);
    
    if (CanPerformAction(unit_entity, &action))
    {
      unit_entity->GetAction(true);
      switch(action.GetType())
      {
          case CAction::IDLE:
              break;
          case CAction::CREATE_PATH:
              CreatePath(unit_entity, &action);
              break;
          case CAction::MOVE:
              Move(unit_entity, &action);
              break;
          case CAction::ATTACK:
              Attack(unit_entity, &action);
              break;
          case CAction::FIGHT:
              Fight(unit_entity, action.GetTarget());
              break;
          case CAction::DIE:
              Die(unit_entity);
              break;
      }
    }
  }
}

bool CUnitControls::CanPerformAction(CUnitEntity* unit_entity, CAction* action, double tmp_sp)
{
  int sp = unit_entity->GetSP();
  
  if (tmp_sp != -1)
  {
    sp = tmp_sp;
  }
  
  if (sp >= action->GetCost()) {
    return true;
  }
  else {
    return false;
  }  
  
}

bool CUnitControls::PerformAction(CUnitEntity* unit_entity, CAction* action) {
  if (CanPerformAction(unit_entity, action))
  {
    unit_entity->DecreaseSP(action->GetCost());
    gui_manager->OnUnitClick(selected_unit);
    return true;    
  }
  else
  {
    return false;
  }
}

bool CUnitControls::CreatePath(CUnitEntity* unit_entity, CAction* action) {
    return CreatePath(unit_entity, action->GetX(), action->GetY());
}

bool CUnitControls::CreatePath(CUnitEntity* unit_entity, int x, int y, double* OUT_sp) {
    double sp = unit_entity->GetSP();
    map->Unblock(unit_entity);
    
    queue< pair<int, int> > path = GeneratePath(unit_entity, x, y);

    while(!path.empty()) {
        pair<int, int>  new_pos = path.front();
        
        CAction action(CAction::MOVE, new_pos.first, new_pos.second, 1);
        if (CanPerformAction(unit_entity, &action, sp))
        {
          unit_entity->AddAction(action);
          sp -= 1;
        }
        else
        {
          return false;
        }
        path.pop();
    }
    
    map->Block(unit_entity);
    
    if (OUT_sp != NULL)
    {
      *OUT_sp = sp;
    }    
    
    return true;
}

void CUnitControls::Move(CUnitEntity* unit_entity, CAction* action) {
  if (!PerformAction(unit_entity, action)) {
    return;
  }

  map->Unblock(unit_entity);
  
  Turn(unit_entity, action->GetX());

  int dx = action->GetX() - unit_entity->GetX();
  int dy = action->GetY() - unit_entity->GetY();

  unit_entity->setPosition(action->GetX(), action->GetY());
  if (unit_entity->GetRefObject() != NULL) {
    unit_entity->GetRefObject()->setPosition(unit_entity->GetRefObject()->GetX()+dx, unit_entity->GetRefObject()->GetY()+dy);
  }


  map->Block(unit_entity);
  map_render->SortObjects(unit_entity);
  if (unit_entity->GetRefObject() != NULL) {
    map_render->SortObjects(unit_entity->GetRefObject());
  }    
}
void CUnitControls::Attack(CUnitEntity* unit_entity, CAction* action) {
  pair<double, double> attacker_pos = unit_entity->GetNearestBlocked(action->GetTarget());

  attacker_pos.first = attacker_pos.first + unit_entity->GetX();
  attacker_pos.second = attacker_pos.second + unit_entity->GetY();  

  pair<double, double> target_pos = action->GetTarget()->GetNearestBlocked(unit_entity);  

  target_pos.first = target_pos.first + action->GetTarget()->GetX();
  target_pos.second = target_pos.second + action->GetTarget()->GetY();


  if (unit_entity->GetRootUnit()->getAttackRange() >= round(CMathUtils::euclidian_distance(target_pos.first, target_pos.second, attacker_pos.first, attacker_pos.second))) {
    if (!PerformAction(unit_entity, action)) {
      return;
    }  
    FireOrFight(unit_entity, action->GetTarget());
  }
  else
  {
    map->Unblock(unit_entity);
    pair<int, int> pos = GetAttackPosition(unit_entity, action->GetTarget());
    map->Block(unit_entity);
    
    double sp = 0;

    if (CreatePath(unit_entity, pos.first, pos.second, &sp))
    {
      CAction action_attack(CAction::ATTACK, action->GetTarget(), 1);
      if (CanPerformAction(unit_entity, &action_attack, sp))
      {
        unit_entity->AddAction(action_attack);
      }
    }    
  }
}

pair<int, int> CUnitControls::GetAttackPosition(CUnitEntity* attacker, CUnitEntity* target) {
  list< pair<int, int> > range_list;
  list< pair<int, int> >::iterator it;

  pair<double, double> attacker_pos = attacker->GetNearestBlocked(target);
  pair<double, double> target_pos = target->GetNearestBlocked(attacker);  
  
  int new_x = 0;
  int new_y = 0;
  double range_value = 0;
  
  for(int i = -attacker->GetRootUnit()->getAttackRange(); i < attacker->GetRootUnit()->getAttackRange(); i++) {
    for(int j = -attacker->GetRootUnit()->getAttackRange(); j < attacker->GetRootUnit()->getAttackRange(); j++) {
      range_value = CMathUtils::euclidian_distance(target->GetX() + target_pos.first + j, target->GetY() + target_pos.second + i, target->GetX() + target_pos.first, target->GetY() + target_pos.second);
      if (round(range_value) <= attacker->GetRootUnit()->getAttackRange()) {
        new_x = target->GetX() + target_pos.first + j - attacker_pos.first;
        new_y = target->GetY() + target_pos.second + i - attacker_pos.second;
        
        if (map->IsPlaceFree(attacker, new_x, new_y)) {
          range_list.push_back(pair<int, int>(new_x, new_y));
        }
      }
    }
  }
  
  double min_value = 999;
  double min_x = 0;
  double min_y = 0;
  double act_value = min_value;
  pair<int, int> pos;
  
  for(it = range_list.begin(); it != range_list.end(); it++) {
    pos = *it;
    
    act_value = CMathUtils::euclidian_distance(pos.first, pos.second, attacker->GetX(), attacker->GetY());
    if (act_value <= min_value) {
      min_value = act_value;
      min_x = pos.first;
      min_y = pos.second;
    }
  }

  return pair<int, int>(min_x, min_y);
}

void CUnitControls::FireOrFight(CUnitEntity* unit_entity, CUnitEntity* target) {
  if (unit_entity->GetRootUnit()->getProjectilID() != -1) {
    int start_x = unit_entity->GetX() + unit_entity->GetRootObject()->GetXSize() / 2;
    int start_y = unit_entity->GetY() + unit_entity->GetRootObject()->GetYSize() / 2;

    CProjectileEntity* proj = object_builder->AddProjectile(start_x, start_y, unit_entity->GetRootUnit()->getProjectilID(), target);
    proj->SetRefObject(unit_entity);
  }
  else {
    Fight(unit_entity, target);
    if (target->GetSP() > 0) {
      CAction action(CAction::FIGHT, unit_entity, 1);
      action.SetPriority(CAction::HIGHEST);
      target->AddAction(action);
    }
  }  
}

void CUnitControls::Fight(CUnitEntity* unit_entity, CUnitEntity* target, bool recursive) {
  int attack_type = unit_entity->GetRootUnit()->GetAttackType(CUtils::Probability(100));

  double attack_str = CMathUtils::gaussian_random(unit_entity->GetRootUnit()->getWeapon(), 2) + (unit_entity->GetRootUnit()->getProp()[STR_IND] / 2) - 2;
  double dexterity_def = unit_entity->GetRootUnit()->getArmor();
  
  Turn(unit_entity, target->GetX());
  
  if (abs(unit_entity->GetDirection() - target->GetDirection()) > 0) {
    dexterity_def += (unit_entity->GetRootUnit()->getProp()[AGL_IND] / 2) - 2;
  }

  double damage = (attack_str - dexterity_def) * ((double)(100-target->GetRootUnit()->getRVP()[attack_type])/100.0);
  
  if (unit_entity->GetRootUnit()->getDamageArea() > 0 && recursive)
  {
    CUnitEntity* unit_entity_near = NULL;
    for(int i = 0; i < map->GetUnitManager()->GetListSize(); i++) {
      unit_entity_near = map->GetUnitManager()->Get(i);
      
      if (CMathUtils::euclidian_distance(unit_entity_near->GetX(), unit_entity_near->GetY(), target->GetX(), target->GetY()) <= unit_entity->GetRootUnit()->getDamageArea())
      {
        Fight(unit_entity, unit_entity_near, false);
      }
    }
  }

  if (damage > 0) {
    CModifier *modifier = (CModifier*)target->AddModifier(new CModifier(IModifier::HURT, 0, target, 1, "hurt", (int)round(damage), -1));
    if (modifier->Apply())
    {
      SDL_Rect position = {(Sint16)(target->GetX() * MAP_ELEM), (Sint16)(target->GetY() * MAP_ELEM), 
                           (Uint16)(target->GetRootUnit()->GetXSize() * MAP_ELEM), (Uint16)(target->GetRootUnit()->GetYSize() * MAP_ELEM)};
      gui_manager->GuiElementManager()->AddOverText(gui_manager->Screen(), position, to_string((int)round(damage)), {255, 0, 0});
    }
  }
  else
  {
    SDL_Rect position = {(Sint16)(target->GetX() * MAP_ELEM), (Sint16)(target->GetY() * MAP_ELEM), 
                         (Uint16)(target->GetRootUnit()->GetXSize() * MAP_ELEM), (Uint16)(target->GetRootUnit()->GetYSize() * MAP_ELEM)};
    gui_manager->GuiElementManager()->AddOverText(gui_manager->Screen(), position, string("Blocked"), {255, 255, 255});    
  }
  
  if (unit_entity->GetRootUnit()->getModifierID() > -1) {
    CModifier *modifier = new CModifier(*modifier_module->GetUnitPtr(unit_entity->GetRootUnit()->getModifierID()));
    
    modifier->SetUnitEntity(target);
    target->AddModifier(modifier);
    
    if (modifier->Apply())
    {
      SDL_Rect position = {(Sint16)(target->GetX() * MAP_ELEM), (Sint16)(target->GetY() * MAP_ELEM), 
                           (Uint16)(target->GetRootUnit()->GetXSize() * MAP_ELEM), (Uint16)(target->GetRootUnit()->GetYSize() * MAP_ELEM)};
      gui_manager->GuiElementManager()->AddOverText(gui_manager->Screen(), position, modifier->GetDesc(), {255, 255, 255});
    }
  }
}

queue< pair<int, int> > CUnitControls::GeneratePath(CUnitEntity* unit_entity, int x, int y) {
  set<int>   closed_set;
  set<int>   open_set;
  int*       came_from;
  
  double *g_score;
  double *f_score;
  
  queue< pair<int, int> > path;
  
  int size_x = map->getMapSizeX(SizeMode::sizemode_elem);
  int size_y = map->getMapSizeY(SizeMode::sizemode_elem);
  CUnit* root_unit = unit_entity->GetRootUnit();
  
  int length = size_x * size_y;
  
  g_score = new double[length];
  memset(g_score, 0, sizeof(double) * length);
  f_score = new double[size_x * size_y];
  memset(f_score, 0, sizeof(double) * length);
  came_from = new int[size_x * size_y];
  memset(came_from, -1, sizeof(int) * length);
  
  int sx = unit_entity->GetX();
  int sy = unit_entity->GetY();
  int gx = x;
  int gy = y;
  
  int start = CMap::compose_node(pair<int, int>(sx, sy), size_x);
  int goal = CMap::compose_node(pair<int, int>(gx, gy), size_x);
  
  double tentative_g_score = 0;
  double cost_sum = 0;
  int current = 0;
  int neighbor = 0;
  pair<int, int> neighbor_nod;
  
  open_set.insert(start);
  g_score[start] = 0;
  f_score[start] = g_score[start] + CMathUtils::euclidian_distance(sx, sy, gx, gy);
  
  while(!open_set.empty()) {
    current = CMathUtils::find_min(&open_set, f_score);
    
    if (current == goal) {
      path = ReconstructPath(came_from, length, goal, size_x);
      return path;
    }
    
    open_set.erase(current);
    closed_set.insert(current);
    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if (i == 1 && j == 1) {
          continue;
        }
        neighbor = current + ((i-1) * size_x + (j-1));
        if (closed_set.count(neighbor) > 0 || neighbor < 0 || neighbor >= length) {
          continue;
        }
        
        tentative_g_score = g_score[current] + CMathUtils::euclidian_distance(0,0,(j-1),(i-1));
        cost_sum = 0;
        
        for(int ik = 0; ik < root_unit->GetYSize(); ik++) {
          for(int jk = 0; jk < root_unit->GetXSize(); jk++) {
            if (root_unit->GetBlockMap()[ik*root_unit->GetYSize()+jk] > 0) {
              cost_sum += map->GetCostMap()[neighbor + (ik * size_x) + jk];
            }
          }
        }
        
        tentative_g_score += cost_sum;
        
        if (open_set.count(neighbor) == 0 || tentative_g_score < g_score[neighbor]) {
          neighbor_nod = CMap::decompose_node(neighbor, size_x);
          came_from[neighbor] = current;
          g_score[neighbor] = tentative_g_score;
          f_score[neighbor] = g_score[neighbor] + CMathUtils::euclidian_distance(neighbor_nod.first, neighbor_nod.second, gx, gy);
          if (open_set.count(neighbor) == 0) {
            open_set.insert(neighbor);
          }
        }
      }
    }
  }
  
  delete f_score;
  delete g_score;
  delete came_from;
  
  return path;
}

queue< pair<int, int> > CUnitControls::ReconstructPath(int* came_from, int length, int current_node, int size_x) {
  if (came_from[current_node] != -1) {
    queue< pair<int, int> > p = ReconstructPath(came_from, length, came_from[current_node], size_x);
    p.push(CMap::decompose_node(current_node, size_x));
    return p;
  }
  else {
    queue< pair<int, int> > p;
    p.push(CMap::decompose_node(current_node, size_x));
    return p;
  }
}

void CUnitControls::Die(CUnitEntity* unit_entity) {
  if (selected_unit == unit_entity)
  {
    DeselectUnit();
  }
  RemoveAttackOnDead(unit_entity);  
  object_builder->RemUnit(unit_entity);
}

void CUnitControls::ResolveModifiers() {
  for(int i = 0; i < map->GetUnitManager()->GetListSize(); i++) {
    ResolveModifier(map->GetUnitManager()->Get(i));
  }
}

void CUnitControls::ResolveModifier(CUnitEntity* unit_entity) {
  vector<IModifier*>* modifier_list = unit_entity->GetModifierList();
  vector<IModifier*>  modifier_list_new;
  bool                list_changed = false;
  
  for(unsigned int j = 0; j < modifier_list->size(); j++) {
    CModifier* modifier = ((CModifier*)modifier_list->at(j));
    CUnitEntity* target = modifier->GetUnitEntity();
    
    if (modifier->Apply())
    {
      SDL_Rect position = { (Sint16)(target->GetX() * MAP_ELEM), (Sint16)(target->GetY() * MAP_ELEM), 
                            (Uint16)(target->GetRootUnit()->GetXSize() * MAP_ELEM), (Uint16)(target->GetRootUnit()->GetYSize() * MAP_ELEM)};

      switch(modifier->GetClass()) {
        case CModifier::HURT:
        case CModifier::BLEED:
          gui_manager->GuiElementManager()->AddOverText(gui_manager->Screen(), position, to_string((int)round(modifier->GetDeltaHP())), {255, 0, 0});
          break;
        case CModifier::HEAL:

          break;
        case CModifier::PARALYZE:
          gui_manager->GuiElementManager()->AddOverText(gui_manager->Screen(), position, modifier->GetDesc(), {255, 255, 255});
          break;
        case CModifier::BREAK:
          break;
        default:
          break;
      }
    }    
  }

  IModifier* del = NULL;
  for(vector<IModifier*>::iterator it = modifier_list->begin(); it != modifier_list->end(); it++) {
    if (((IModifier*)*it)->GetDuration() == 0) {
      del = *it;
      delete del;
      list_changed = true;
    }
    else {
      modifier_list_new.push_back(*it);
    }
  }
  
  if(list_changed) {
    modifier_list->clear();
    modifier_list->insert(modifier_list->begin(), modifier_list_new.begin(), modifier_list_new.end());
  }
}

void CUnitControls::DeselectUnit()
{
  if (selected_unit != NULL) {
    object_builder->RemObject(selected_unit->GetRefObject()->GetID());
    selected_unit->SetRefObject(NULL);
    selected_unit->SetSelected(false);            
    selected_unit = NULL;
    gui_manager->OnUnitClick(selected_unit);  
  }
}

void CUnitControls::RemoveAttackOnDead(CUnitEntity* dead)
{
  CUnitEntity*  unit_entity = NULL;
  CAction       action;
  
  for(int i = 0; i < map->GetUnitManager()->GetListSize(); i++) {
    unit_entity = map->GetUnitManager()->Get(i);
    action = unit_entity->GetAction(false);
    
    if (action.GetType() == CAction::ATTACK && action.GetTarget() == dead)
    {
      unit_entity->ClearActionQueue();
    }
  }
}

void CUnitControls::Turn(CUnitEntity* unit_entity, int x)
{
  if (unit_entity->GetX() > x&& unit_entity->GetDirection() != CUnitEntity::LEFT) {
    CAction action(CAction::MOVE, 1);
    if (PerformAction(unit_entity, &action))
    {
      unit_entity->SetDirection(CUnitEntity::LEFT);
    }
  }
  if (unit_entity->GetX() < x && unit_entity->GetDirection() != CUnitEntity::RIGHT) {
    CAction action(CAction::MOVE, 1);
    if (PerformAction(unit_entity, &action))
    {
      unit_entity->SetDirection(CUnitEntity::RIGHT);
    }
  }  
}