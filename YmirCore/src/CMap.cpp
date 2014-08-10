/* 
 * File:   CMap.cpp
 * Author: Matej Pechac
 * 
 * Created on August 20, 2012, 5:41 PM
 */

#include <math.h>

#include "CMap.h"
#include "GlobalDefine.h"
#include "CStrUtils.h"
#include "CMathUtils.h"

CMap::CMap(CModule<CTile>* tile_module, CModule<CUnit> *unit_module, CModule<CObject> *object_module) 
    : CObjectManager(object_module) {  
  this->tile_module = tile_module;
  this->unit_module = unit_module;
  this->object_module = object_module;
  map_segsize_x = 0;
  map_segsize_y = 0;
  map_tilesize_x = 0;
  map_tilesize_y = 0;
  map_elemsize_x = 0;
  map_elemsize_y = 0;

  pTile = NULL;
  move_cost_map = NULL;
  
  unit_manager = new CUnitManager(unit_module, this);
}

CMap::CMap(int x, int y, int default_tile, CModule<CTile> *tile_module, CModule<CUnit> *unit_module, CModule<CObject> *object_module) 
    : CObjectManager(object_module) {
  map_segsize_x = x;
  map_segsize_y = y;
  map_tilesize_x = x * TILE_PER_SEGMENT;
  map_tilesize_y = y * TILE_PER_SEGMENT;
  map_elemsize_x = x * TILE_PER_SEGMENT * ELEM_PER_TILE;
  map_elemsize_y = y * TILE_PER_SEGMENT * ELEM_PER_TILE;
  
  this->tile_module = tile_module;
  this->unit_module = unit_module;
  this->object_module = object_module;

  pTile = new CTile*[map_tilesize_x*map_tilesize_y];
  
  for(int i = 0; i < map_tilesize_x*map_tilesize_y; i++) {
    pTile[i] = tile_module->GetUnitPtr(default_tile);
  }
  
  move_cost_map = new double[map_elemsize_x*map_elemsize_y];
  memset(move_cost_map, 0, map_elemsize_x*map_elemsize_y*sizeof(double));
  unit_manager = new CUnitManager(unit_module, this);
}

CMap::CMap(const CMap& orig) : CObjectManager(orig) {
  map_segsize_x = orig.map_segsize_x;
  map_segsize_x = orig.map_segsize_x;
  map_tilesize_x = orig.map_tilesize_x;
  map_tilesize_y = orig.map_tilesize_y;
  map_elemsize_x = orig.map_elemsize_x;
  map_elemsize_y = orig.map_elemsize_y;
  pTile = orig.pTile;
  move_cost_map = orig.move_cost_map;
  tile_module = orig.tile_module;
  unit_module = orig.unit_module;
  object_module = orig.object_module;
  unit_manager = orig.unit_manager;
}

CMap::~CMap() {
  delete[] pTile;
  delete[] move_cost_map;
}

int CMap::Save(string filename) {
  ofstream file;
  char val[4+1];
  
  CStrUtils::EraseBuffer(val, 4);
  
  file.open(filename.c_str(), ios::out | ios::binary);
  
  if (write_header(&file) != 0) {
    return -1;
  }
  
  for(int i = 0; i < map_tilesize_y; i++) {
    for(int j = 0; j < map_tilesize_x; j++) {
      sprintf(val, "%i", (pTile[i*map_tilesize_x+j])->GetID());
      file.write(val, 4);
      CStrUtils::EraseBuffer(val, 4);      
    }
  }
  
  file.close();
  
  return 0;
}

int CMap::write_header(ofstream* stream) {
  char val[16+1];
  
  CStrUtils::EraseBuffer(val, 16);

  sprintf(val, "%i", name.size());
  stream->write(val, 4);
  CStrUtils::EraseBuffer(val, 16);
  stream->write(name.c_str(), name.size());
  sprintf(val, "%i", map_segsize_x);
  stream->write(val, 16);
  CStrUtils::EraseBuffer(val, 16);
  sprintf(val, "%i", map_segsize_y);
  stream->write(val, 16);
  CStrUtils::EraseBuffer(val, 16);
  sprintf(val, "%i", map_tilesize_x);
  stream->write(val, 16);
  CStrUtils::EraseBuffer(val, 16);
  sprintf(val, "%i", map_tilesize_y);
  stream->write(val, 16);
  CStrUtils::EraseBuffer(val, 16);
  sprintf(val, "%i", map_elemsize_x);
  stream->write(val, 16);
  CStrUtils::EraseBuffer(val, 16);
  sprintf(val, "%i", map_elemsize_y);
  stream->write(val, 16);
  

  return 0;  
}

int CMap::Load(string filename) {
  ifstream file;
  char val[4+1];
  
  file.open(filename.c_str(), ios::in | ios::binary);

  if (read_header(&file) != 0) {
    return -1;
  }
  
  if (pTile != NULL) {
    delete[] pTile;
  }
  
  pTile = new CTile*[map_tilesize_x * map_tilesize_y];
  
  for(int i = 0; i < map_tilesize_y; i++) {
    for(int j = 0; j < map_tilesize_x; j++) {
      file.read(val, 4);
      pTile[i*map_tilesize_x + j] = tile_module->GetUnitPtr(atoi(val));
    }
  }
  
  if (move_cost_map != NULL) {
    delete[] move_cost_map;
  }
  
  move_cost_map = new double[map_elemsize_x*map_elemsize_y];
  memset(move_cost_map, 0, map_elemsize_x*map_elemsize_y*sizeof(double));
  
  file.close();
  
  return 0;
}

int CMap::read_header(ifstream* stream) {
  char  *temp;
  int   temp_size = 0;
  char  val[16+1];
  
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 4);
  temp_size = atoi(val);
  temp = new char[temp_size];
  CStrUtils::EraseBuffer(temp, temp_size);
  stream->read(temp, temp_size);
  name = string(temp);
  
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 16);
  map_segsize_x = atoi(val);
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 16);
  map_segsize_y = atoi(val);
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 16);
  map_tilesize_x = atoi(val);
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 16);
  map_tilesize_y = atoi(val);
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 16);
  map_elemsize_x = atoi(val);
  CStrUtils::EraseBuffer(val, 16);
  stream->read(val, 16);
  map_elemsize_y = atoi(val);  
  return 0;
}

void CMap::generateMap(int c_earth, int c_water, int c_air, int c_fire) {
  /* Vygenerovanie suradnic centroidov */
  vector< pair<int, int> > earth_nodes;
  vector< pair<int, int> > water_nodes;
  vector< pair<int, int> > air_nodes;
  vector< pair<int, int> > fire_nodes;

  for(int i = 0; i < c_earth; i++) {
    pair<int, int> tmp_pair;
    tmp_pair.first  = rand() % map_tilesize_x;
    tmp_pair.second = rand() % map_tilesize_y;
    earth_nodes.push_back(tmp_pair);
  }

  for(int i = 0; i < c_water; i++) {
    pair<int, int> tmp_pair;
    tmp_pair.first  = rand() % map_tilesize_x;
    tmp_pair.second = rand() % map_tilesize_y;
    water_nodes.push_back(tmp_pair);
  }

  for(int i = 0; i < c_air; i++) {
    pair<int, int> tmp_pair;
    tmp_pair.first  = rand() % map_tilesize_x;
    tmp_pair.second = rand() % map_tilesize_y;
    air_nodes.push_back(tmp_pair);
  }

  for(int i = 0; i < c_fire; i++) {
    pair<int, int> tmp_pair;
    tmp_pair.first  = rand() % map_tilesize_x;
    tmp_pair.second = rand() % map_tilesize_y;
    fire_nodes.push_back(tmp_pair);
  }

  /* Vypocet hodnot pre jednotlive tiley na zaklade vzdialenosti od centroidov */
  pair<int, int> tmp_pair;
  double e_dist = 0, g_dist = 0;
  int sigma = sqrt(max(map_tilesize_x, map_tilesize_y));
  
  for(int i = 0; i < map_tilesize_x; i++) {
    for(int j = 0; j < map_tilesize_y; j++) {
      CTile tile;

      for(int n = 0; n < c_earth; n++) {
        tmp_pair = earth_nodes.at(n);
        e_dist = CMathUtils::euclidian_distance(j, i, tmp_pair.first, tmp_pair.second);
        g_dist = gaussian_distance(sigma, pow(e_dist, 2));
        tile.setEarth(max(g_dist, tile.getEarth()));
      }

      for(int n = 0; n < c_water; n++) {
        tmp_pair = water_nodes.at(n);
        e_dist = CMathUtils::euclidian_distance(j, i, tmp_pair.first, tmp_pair.second);
        g_dist = gaussian_distance(sigma, pow(e_dist, 2));
        tile.setWater(max(g_dist, tile.getWater()));
      }

      for(int n = 0; n < c_air; n++) {
        tmp_pair = air_nodes.at(n);
        e_dist = CMathUtils::euclidian_distance(j, i, tmp_pair.first, tmp_pair.second);
        g_dist = gaussian_distance(sigma, pow(e_dist, 2));
        tile.setAir(max(g_dist, tile.getAir()));
      }

      for(int n = 0; n < c_fire; n++) {
        tmp_pair = fire_nodes.at(n);
        e_dist = CMathUtils::euclidian_distance(j, i, tmp_pair.first, tmp_pair.second);
        g_dist = gaussian_distance(sigma, pow(e_dist, 2));
        tile.setFire(max(g_dist, tile.getFire()));
      }

      normalize_tile(&tile);
      //pTile[i*map_tilesize_y+j] = tile;
    }
  }
}

double CMap::gaussian_distance(double sigma, double numerator) {
	double g = 0;

	g = exp(-(numerator/(2*pow(sigma, 2))));

	return g;
}

void CMap::normalize_tile(CTile* p_tile) {
  double norm = 0;

  norm = pow(p_tile->getAir(), 2) + pow(p_tile->getEarth(), 2) + pow(p_tile->getFire(), 2) + pow(p_tile->getWater(), 2);
  norm = sqrt(norm);
  /*
  p_tile->air /= norm;
  p_tile->earth /= norm;
  p_tile->fire /= norm;
  p_tile->water /= norm;
  */
  return;
}

void CMap::addUnit(int x, int y, int id, int player_id)  {
  CUnitEntity* unit_entity = unit_manager->addUnit(x, y, id, player_id);
  Block(unit_entity);
  player_manager->GetPlayer(player_id)->AddUnit(unit_entity);
}

int CMap::getMapSizeX(SizeMode mode) {
  if (mode == sizemode_segment) {
    return this->map_segsize_x;
  }
  if (mode == sizemode_tile) {
    return this->map_tilesize_x;
  }
  if (mode == sizemode_elem) {
    return this->map_elemsize_x;
  }
  return -1;
}

int CMap::getMapSizeY(SizeMode mode) {
  if (mode == sizemode_segment) {
    return this->map_segsize_y;
  }
  if (mode == sizemode_tile) {
    return this->map_tilesize_y;
  }
  if (mode == sizemode_elem) {
    return this->map_elemsize_y;
  }  
  return -1; 
}

pair<int, int> CMap::decompose_node(int mixed, int size_x) {
  pair<int, int> node(mixed % size_x, mixed / size_x);
  
  return node;
}

int CMap::compose_node(pair<int, int> node, int size_x) {
  int mixed = node.second * size_x + node.first;
  
  return mixed;
}

void CMap::Block(CUnitEntity* unit_entity) {
  for(int i = 0; i < unit_entity->GetRootUnit()->GetYSize(); i++) {
    for(int j = 0; j < unit_entity->GetRootUnit()->GetXSize(); j++) {
      int node = CMap::compose_node(pair<int, int>(unit_entity->GetX() + j, unit_entity->GetY() + i), map_elemsize_x);
      int local_node = i*unit_entity->GetRootUnit()->GetXSize() + j;
      move_cost_map[node] += unit_entity->GetRootUnit()->GetBlockMap()[local_node];
    }
  }
}

void CMap::Unblock(CUnitEntity* unit_entity) {
  for(int i = 0; i < unit_entity->GetRootObject()->GetYSize(); i++) {
    for(int j = 0; j < unit_entity->GetRootObject()->GetXSize(); j++) {
      int node = CMap::compose_node(pair<int, int>(unit_entity->GetX() + j, unit_entity->GetY() + i), map_elemsize_x);
      int local_node = i*unit_entity->GetRootObject()->GetXSize() + j;
      move_cost_map[node] -= unit_entity->GetRootObject()->GetBlockMap()[local_node];
    }
  }  
}

bool CMap::IsPlaceFree(CUnitEntity* unit_entity, int x, int y) {
  for(int i = 0; i < unit_entity->GetRootObject()->GetYSize(); i++) {
    for(int j = 0; j < unit_entity->GetRootObject()->GetXSize(); j++) {
      int node = CMap::compose_node(pair<int, int>(x + j, y + i), map_elemsize_x);
      if (move_cost_map[node] == 99) {
        return false;
      }
    }
  }
  return true;
}