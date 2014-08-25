/* 
 * File:   CUnit.cpp
 * Author: Matej Pechac
 * 
 * Created on August 20, 2012, 5:42 PM
 */

#include "CUnit.h"
#include "CStrUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CUnit::CUnit() : CObject() {
  this->aa = 0;
  this->ar = 0;
  this->sr = 0;
  this->unit_class = "";
  this->unit_race = "";
  
  for(unsigned int i = 0; i < N_PROP; i++) {
    unit_props.push_back(0);
  }
  
  for(unsigned int i = 0; i < N_ELEM; i++) {
    elements.push_back(0);
  }
  
  for(unsigned int i = 0; i < N_ATTACK; i++) {
    avp.push_back(0);
    rvp.push_back(0);
  }
}

CUnit::CUnit(int id) : CObject(id)  {
  this->aa = 0;
  this->ar = 0;
  this->image_filename = "";
  this->sr = 0;
  this->unit_class = "";
  this->unit_race = "";
  
  for(unsigned int i = 0; i < N_PROP; i++) {
    unit_props.push_back(0);
  }
  
  for(unsigned int i = 0; i < N_ELEM; i++) {
    elements.push_back(0);
  }
  
  for(unsigned int i = 0; i < N_ATTACK; i++) {
    avp.push_back(0);
    rvp.push_back(0);
  }
}

CUnit::CUnit(map<string,string> data) : CObject(data){
  char key[100+1];
    
  unit_class = data["unit_class"];
  unit_race = data["unit_race"];
    
  for(unsigned int i = 0; i < N_PROP; i++) {
    sprintf(key, "prop%i", i);
    unit_props.push_back(atoi(data[key].c_str()));
  }
  
  sr = atoi(data["sr"].c_str());
  ar = atoi(data["ar"].c_str());
  aa = atoi(data["aa"].c_str());
  
  for(unsigned int i = 0; i < N_ELEM; i++) {
    sprintf(key, "elem%i", i);
    elements.push_back(atoi(data[key].c_str()));
  }
  
  for(unsigned int i = 0; i < N_ATTACK; i++) {
    sprintf(key, "avp%i", i);
    avp.push_back(stoi(data[key]));
  }

  for(unsigned int i = 0; i < N_ATTACK; i++) {
    sprintf(key, "rvp%i", i);
    rvp.push_back(stoi(data[key]));
  }
  
  insignia_pos.first = atoi(data["ins_x"].c_str());
  insignia_pos.second = atoi(data["ins_y"].c_str());
}

CUnit::CUnit(const CUnit& orig) : CObject(orig) {
  this->aa = orig.aa;
  this->ar = orig.ar;
  this->avp = orig.avp;
  this->elements = orig.elements;
  this->rvp = orig.rvp;
  this->sr = orig.sr;
  this->unit_class = orig.unit_class;
  this->unit_props = orig.unit_props;
  this->unit_race = orig.unit_race;
  this->insignia_pos = orig.insignia_pos;
}

CUnit::~CUnit() {
  if (block_map != NULL) {
    //delete[] block_map;
  }
}

map<string, string> CUnit::exportMap() {
  map<string, string> result = CObject::exportMap();
  char key[100+1];
  char val[100+1];
  
  result["unit_class"] = unit_class;
  result["unit_race"] = unit_race;
  
  for(unsigned int i = 0; i < unit_props.size(); i++) {
    sprintf(key, "prop%i", i);
    sprintf(val, "%i", unit_props[i]);
    result[key] = val;
  }
  
  sprintf(val, "%i", sr);
  result["sr"] = val;
  sprintf(val, "%i", ar);
  result["ar"] = val;
  sprintf(val, "%i", aa);
  result["aa"] = val;
  
  for(unsigned int i = 0; i < elements.size(); i++) {
    sprintf(key, "elem%i", i);
    sprintf(val, "%i", elements[i]);
    result[key] = val;
  }
  
  for(unsigned int i = 0; i < avp.size(); i++) {
    sprintf(key, "avp%i", i);
    result[key] = to_string(avp[i]);
  }

  for(unsigned int i = 0; i < rvp.size(); i++) {
    sprintf(key, "rvp%i", i);
    result[key] = to_string(rvp[i]);
  }
  
  result["ins_x"] = to_string(insignia_pos.first);
  result["ins_y"] = to_string(insignia_pos.second);

  return result;
}

void CUnit::setProp(vector<int> unit_props) {
  this->unit_props = unit_props;
}

vector<int> CUnit::getProp() {
  return unit_props;
}

void CUnit::setClass(string _class) {
  this->unit_class = _class;
}

string CUnit::getClass() {
  return unit_class;
}

void CUnit::setRace(string _race) {
  unit_race = _race;
}

string CUnit::getRace() {
  return unit_race;
}

void CUnit::setElem(vector<int> _elem) {
  this->elements = _elem;
}

vector<int> CUnit::getElem() {
  return elements;
}

void CUnit::setAVP(vector<int> _avp) {
  this->avp = _avp;
}

vector<int> CUnit::getAVP() {
  return avp;
}

int CUnit::GetAttackType(double probability) {
  int avp_prob = 0;
  
  for(int i = 0; i < N_ATTACK; i++) {
    if (probability >= avp_prob && probability < (avp_prob + avp[i])) {
      return i;
    }
    avp_prob += avp[i];
  }
  
  return -1;
}

void CUnit::setRVP(vector<int> _rvp) {
  this->rvp = _rvp;
}

vector<int> CUnit::getRVP() {
  return rvp;
}

void CUnit::setSight(int _sr) {
  this->sr = _sr;
}

int CUnit::getSight() {
  return sr;
}

void CUnit::setAttackRange(int _ar) {
  this->ar = _ar;
}

int CUnit::getAttackRange() {
  return ar;
}

void CUnit::setDamageArea(int _aa) {
  this->aa = _aa;
}

int CUnit::getDamageArea() {
  return aa;
}

void CUnit::setInsigniaPos(pair<int,int> pos) {
  this->insignia_pos = pos;
}

pair<int, int> CUnit::getInsigniaPos() {
  return insignia_pos;
}