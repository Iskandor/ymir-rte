/* 
 * File:   CProjectile.cpp
 * Author: Matej Pechac
 * 
 * Created on September 14, 2014, 11:10 PM
 */

#include "CProjectile.h"

CProjectile::CProjectile() : CObject() {
}

CProjectile::CProjectile(map<string,string> data) : CObject(data) {
  speed = stoi(data["speed"]);
}

CProjectile::CProjectile(const CProjectile& orig) : CObject(orig) {
  speed = orig.speed;
  
}

CProjectile::~CProjectile() {
}

map<string, string> CProjectile::exportMap()  {
  map<string, string> result = CObject::exportMap();
  
  result["speed"] = to_string(speed);
  
  return result;
}

