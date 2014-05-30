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

using namespace std;

enum SizeMode {
  sizemode_segment,
  sizemode_tile,
  sizemode_elem
};

class CMap : public CObjectManager {
public:
  CMap(CModule<CTile> *tile_module, CModule<CUnit> *unit_module, CModule<CObject> *object_module);
  CMap(int x, int y, int default_tile, CModule<CTile> *tile_module, CModule<CUnit> *unit_module, CModule<CObject> *object_module);
  CMap(const CMap& orig);
  virtual ~CMap();
private:
  CModule<CTile>    *tile_module;
  CModule<CUnit>    *unit_module;
  CModule<CObject>  *object_module;
  CUnitManager      *unit_manager;
  
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

  CTile**  getTilePtr() { return this->pTile; };
  double*  GetCostMap() { return this->move_cost_map; };

  int getMapSizeX(SizeMode mode);
  int getMapSizeY(SizeMode mode);
  
  CUnitManager* GetUnitManager() { return unit_manager; };
  
  void addUnit(int x, int y, int id);
  
  void Block(CUnitEntity* unit_entity);
  void Unblock(CUnitEntity* unit_entity);
  
  static pair<int, int> decompose_node(int mixed, int size_x);
  static int            compose_node(pair<int, int> node, int size_x);
};

#endif	/* CMAP_H */

