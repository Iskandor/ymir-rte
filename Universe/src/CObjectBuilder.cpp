/* 
 * File:   CObjectBuilder.cpp
 * Author: Matej Pechac
 * 
 * Created on May 11, 2015, 7:39 PM
 */

#include "CObjectBuilder.h"

CObjectBuilder::CObjectBuilder(CMap *map, CMapRender *map_render) {
  this->map = map;
  this->map_render = map_render;
}

CObjectBuilder::CObjectBuilder(const CObjectBuilder& orig) {
  this->map = orig.map;
  this->map_render = orig.map_render;
}

CObjectBuilder::~CObjectBuilder() {
}

CObjectEntity* CObjectBuilder::AddObject(int x, int y, double z_index, int class_id, CObject* object)
{
  CObjectEntity* object_entity = map->addObject(x, y, class_id, object);
  map_render->AddObject(object_entity, z_index);
  
  return object_entity;
}

CObjectEntity* CObjectBuilder::AddObject(CObjectEntity* object_entity, double z_index)
{
  CObjectEntity* tmp_object_entity = map->addObject(object_entity);
  map_render->AddObject(tmp_object_entity, z_index);
  
  return tmp_object_entity;  
}

CUnitEntity* CObjectBuilder::AddUnit(int x, int y, int id, int player_id)
{
  CUnitEntity* unit_entity = map->addUnit(x, y, id, player_id);
  map_render->AddUnit(unit_entity, MIDDLE);
  
  return unit_entity;
}

CProjectileEntity* CObjectBuilder::AddProjectile(int x, int y, int id, CUnitEntity* target)
{
  CProjectileEntity* projectile_entity = map->addProj(x, y, id, target);
  map_render->AddProjectile(projectile_entity, TOP);
  
  return projectile_entity;
}

void CObjectBuilder::RemObject(int id)
{
  map->remObject(id);
  map_render->RemObject(id);
}

void CObjectBuilder::RemUnit(CUnitEntity* unit_entity)
{
  map->remUnit(unit_entity);
  map_render->RemUnit(unit_entity->GetID());
}

void CObjectBuilder::RemProjectile(CProjectileEntity* projectile_entity)
{
  map->remProj(projectile_entity);
  map_render->RemProjectile(projectile_entity->GetID());  
}

