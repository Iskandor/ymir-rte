/* 
 * File:   CObjectBuilder.h
 * Author: Matej Pechac
 *
 * Created on May 11, 2015, 7:39 PM
 */

#ifndef COBJECTBUILDER_H
#define	COBJECTBUILDER_H

#include "CMap.h"
#include "CMapRender.h"

class CObjectBuilder {
public:
  CObjectBuilder(CMap *map, CMapRender *map_render);
  CObjectBuilder(const CObjectBuilder& orig);
  virtual ~CObjectBuilder();

  CObjectEntity*      AddObject(int x, int y, double z_index, int class_id, CObject* object = NULL);
  CObjectEntity*      AddObject(CObjectEntity* object_entity, double z_index);
  void                RemObject(int id);
  CUnitEntity*        AddUnit(int x, int y, int id, int player_id);
  void                RemUnit(CUnitEntity* unit_entity);
  CProjectileEntity*  AddProjectile(int x, int y, int id, CUnitEntity* target);
  void                RemProjectile(CProjectileEntity* projectile_entity);  
  
private:
  CMap         *map;
  CMapRender   *map_render;
};

#endif	/* COBJECTBUILDER_H */

