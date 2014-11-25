/* 
 * File:   CTile.cpp
 * Author: Matej Pechac
 * 
 * Created on October 30, 2013, 11:56 PM
 */

#include "CTile.h"
#include <stdlib.h>
#include <stdio.h>

CTile::CTile() : ISerializable() {
  this->id = 0;
  this->air = 0.0;
  this->earth = 0.0;
  this->fire = 0.0;
  this->water = 0.0;  
}

CTile::CTile(int id) : ISerializable() {
  this->id = id;
  this->air = 0.0;
  this->earth = 0.0;
  this->fire = 0.0;
  this->water = 0.0;
}

CTile::CTile(map<string,string> data) : ISerializable(data) {
  id = atoi(data["id"].c_str());
  name = data["name"];
  filename = data["filename"];
  this->air = 0.0;
  this->earth = 0.0;
  this->fire = 0.0;
  this->water = 0.0;  
}

CTile::CTile(const CTile& orig) : ISerializable(orig) {
  this->id = orig.id;
  this->air = orig.air;
  this->earth = orig.earth;
  this->fire = orig.fire;
  this->water = orig.water;
  this->name = orig.name;
  this->filename = orig.filename;
}

CTile::~CTile() {
}

map<string, string> CTile::exportMap() {
  map<string, string> result;
  char  val[100+1];
  
  sprintf(val, "%i", id);
  result["id"] = val;
  result["name"] = name;
  result["filename"] = filename;
  
  return result;
}

double CTile::getAir() {
  return this->air;
}

double CTile::getEarth() {
  return this->earth;
}

double CTile::getFire() {
  return this->fire;
}

double CTile::getWater() {
  return this->water;
}

string CTile::getName() {
  return name;
}

string CTile::getFilename() {
  return filename;
}

int CTile::GetID() {
  return id;
}

void CTile::setEarth(double value) {
  earth = value;
}

void CTile::setWater(double value) {
  water = value;
}

void CTile::setAir(double value) {
  air = value;
}

void CTile::setFire(double value) {
  fire = value;
}

void CTile::setName(string name) {
  this->name = name;
}

void CTile::setFilename(string filename) {
  this->filename = filename;
}

void CTile::SetID(int id) {
  this->id = id;
}

