/* 
 * File:   CTile.h
 * Author: Matej Pechac
 *
 * Created on October 30, 2013, 11:56 PM
 */

#ifndef CTILE_H
#define	CTILE_H

#include "GlobalDefine.h"
#include <map>
#include <string>

using namespace std;

class CTile {
public:
  CTile();
  CTile(int id);
  CTile(map<string, string> data);
  CTile(const CTile& orig);
  virtual ~CTile();
  
public:
  map<string, string> exportMap();
  
  double getEarth();
  double getWater();
  double getAir();
  double getFire();
  string getName();
  string getFilename();
  int    GetID();
  int    GetTypeID() { return id; };
  
  void setEarth(double value);
  void setWater(double value);
  void setAir(double value);
  void setFire(double value);
  void setName(string name);
  void setFilename(string filename);
  void SetID(int id);
  
private:
  double   earth;
  double   water;
  double   air;
  double   fire;
  
  int      id;
  string   name;
  string   filename;
  
  double   move_cost_map[ELEM_PER_TILE * ELEM_PER_TILE];
};

#endif	/* CTILE_H */

