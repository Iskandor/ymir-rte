/* 
 * File:   CObject.cpp
 * Author: Matej Pechac
 * 
 * Created on May 10, 2014, 11:02 AM
 */

#include <string.h>
#include <cstdlib>
#include <cstdio>
#include "CObject.h"
#include "CStrUtils.h"


CObject::CObject() : ISerializable() {
  id = 0;
  type_id = 0;
  x_size = y_size = 0;
  block_map = NULL;
  image_filename = "";
  desc = "";
  obj_class = CObject::TECH;
}

CObject::CObject(int id) : ISerializable() {
  this->id = id;
  type_id = id;
  x_size = y_size = 0;
  block_map = NULL;
  image_filename = "";
  desc = "";
  obj_class = CObject::TECH;
}

CObject::CObject(const CObject& orig) : ISerializable(orig) {
  id = orig.id;
  x_size = orig.x_size;
  y_size = orig.y_size;
  block_map = new int[x_size*y_size];
  memcpy(block_map, orig.block_map, x_size*y_size*sizeof(int));
  image_filename = orig.image_filename;
  desc = orig.desc;
  obj_class = orig.obj_class;
  type_id = orig.type_id;
}

CObject::CObject(map<string, string> data) : ISerializable(data) {
  block_map = NULL;
  
  id = atoi(data["id"].c_str());
  type_id = id;
  obj_class = (CObject::E_CLASSES)stoi(data["obj_class"]);
  image_filename = data["image_filename"];
  desc = data["desc"];
  x_size = atoi(data["x_size"].c_str());
  y_size = atoi(data["y_size"].c_str());
  
  SetBlockMap(x_size, y_size);
  
  CStrUtils::ExplodeFromString(data["block_map"], block_map);  
}

CObject::~CObject() {
}

map<string, string> CObject::exportMap() {
  map<string, string> result;
  char val[100+1];
  
  sprintf(val, "%i", id);
  result["id"] = val;
  result["obj_class"] = to_string(obj_class);
  
  result["image_filename"] = image_filename;
  result["desc"] = desc;
  
  sprintf(val, "%i", x_size);
  result["x_size"] = val;
  sprintf(val, "%i", y_size);
  result["y_size"] = val;

  result["block_map"] = CStrUtils::ImplodeToString(block_map, x_size*y_size); 
  
  return result;
}

void CObject::SetID(int id) {
  this->id = id;
}

int CObject::GetID() {
  return id;
}

void CObject::SetImage(string _image) {
  image_filename = _image;
}

string CObject::GetImage() {
  return image_filename;
}

void CObject::SetDesc(string desc) {
  this->desc = desc;
}

string CObject::GetDesc() {
  return desc;
}

int CObject::GetXSize() {
  return x_size;
}

void CObject::SetXSize(int x) {
  if (y_size > 0 && x_size != x) {
    SetBlockMap(x, y_size);
  }
  this->x_size = x;   
}

int CObject::GetYSize() {
  return y_size;
}

void CObject::SetYSize(int y) {
  if (x_size > 0 && y_size != y) {
    SetBlockMap(x_size, y);
  }  
  this->y_size = y;
}

int* CObject::GetBlockMap() {
  return block_map;
}

void CObject::SetBlockMap(int x, int y) {
  if (block_map != NULL) {
    delete[] block_map;
  }
  block_map = new int[x * y];
  
  memset(block_map, 0, x*y*sizeof(int));  
}

void CObject::SetBlockMap(int* block_map) {
  this->block_map = block_map;
}