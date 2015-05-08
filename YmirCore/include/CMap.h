/* 
 * File:   CMap.h
 * Author: Matej Pechac
 *
 * Created on August 20, 2012, 5:41 PM
 */

#ifndef CMAP_H
#define	CMAP_H

#include <vector>
#include <string>
#include <fstream>

#include "CTile.h"
#include "CObjectManager.h"
#include "CUnitManager.h"
#include "CPlayerManager.h"
#include "CProjectileManager.h"

using namespace std;

enum SizeMode {
  sizemode_segment,
  sizemode_tile,
  sizemode_elem
};

class CMap : public CObjectManager {
public:
  CMap();
  CMap(CModule<CTile> *tile_module, CModule<CUnit> *unit_module, CModule<CObject> *object_module, CModule<CProjectile> *projectile_module);
  CMap(int x, int y, int default_tile, CModule<CTile> *tile_module, CModule<CUnit> *unit_module, CModule<CObject> *object_module, CModule<CProjectile> *projectile_module);
  CMap(const CMap& orig);
  virtual ~CMap();
private:
  CModule<CTile>        *tile_module;
  CModule<CUnit>        *unit_module;
  CModule<CObject>      *object_module;
  CModule<CProjectile>  *projectile_module;
  CUnitManager          *unit_manager;
  CPlayerManager        *player_manager;
  CProjectileManager    *projectile_manager;
    
  string  name;
  string  filename;

  int map_segsize_x;
  int map_segsize_y;
  int map_tilesize_x;
  int map_tilesize_y;
  int map_elemsize_x;
  int map_elemsize_y;  
  
  CTile** pTile;
  
  double  *move_cost_map;
  
  int write_header(ofstream* stream);
  int read_header(ifstream* stream);  

  double gaussian_distance(double sigma, double numerator);
  void   normalize_tile(CTile* p_tile);
  
  void set_cost_map(int x, int y, double cost);

public:
  int Save(string filename);
  int Load(string filename);
  
  void generateMap(int c_earth, int c_water, int c_air, int c_fire);

  void setName(string name) {this->name = name;};
  string getName() { return this->name;};
  
  void SetPlayerManager(CPlayerManager* player_manager) { this->player_manager = player_manager; };
  CPlayerManager* GetPlayerManager() { return player_manager; };

  CTile**  getTilePtr() { return this->pTile; };
  double*  GetCostMap() { return this->move_cost_map; };

  int getMapSizeX(SizeMode mode);
  int getMapSizeY(SizeMode mode);
  
  CUnitManager* GetUnitManager() { return unit_manager; };
  CProjectileManager* GetProjectileManager() { return projectile_manager; };
  
  CUnitEntity* addUnit(int x, int y, int id, int player_id);
  void remUnit(CUnitEntity* unit_entity);
  CProjectileEntity* addProj(int x, int y, int id, CUnitEntity* target);
  void remProj(CProjectileEntity* projectile_entity);
  
  void Block(CUnitEntity* unit_entity);
  void Unblock(CUnitEntity* unit_entity);
  bool IsPlaceFree(CUnitEntity* unit_entity, int x, int y);
  void SortObjects(CObjectEntity* object_entity);
  
  static pair<int, int> decompose_node(int mixed, int size_x);
  static int            compose_node(pair<int, int> node, int size_x);
};

#endif	/* CMAP_H */

