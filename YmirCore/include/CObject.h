/* 
 * File:   CObject.h
 * Author: Matej Pechac
 *
 * Created on May 10, 2014, 11:02 AM
 */

#ifndef COBJECT_H
#define	COBJECT_H

#include <string>
#include <map>

#include "ISerializable.h"

using namespace std;

class CObject : public ISerializable {
public:
  enum E_CLASSES {
    TECH = 0,
    PROJECTILE = 1,
    UNIT = 2
  };
  
  CObject();
  CObject(int id);
  CObject(map<string, string> data);
  CObject(const CObject& orig);
  virtual ~CObject();
  
  map<string, string> exportMap();
  
  void    SetImage(string _image);
  string  GetImage(); 
  void    SetDesc(string desc);
  string  GetDesc();
  
  void  SetID(int id);
  int   GetID();
  int   GetTypeID() { return type_id; }
  void  SetClass(E_CLASSES value) { obj_class = value; };
  int   GetClass() { return obj_class; };
  int   GetXSize();
  void  SetXSize(int x);
  int   GetYSize();
  void  SetYSize(int y);
  int*  GetBlockMap();
  void  SetBlockMap(int x, int y);
  void  SetBlockMap(int* block_map);  
  
protected:
  int id;
  int type_id;
  E_CLASSES obj_class;
  int x_size;
  int y_size;
  int *block_map;
  
  string image_filename;
  string desc;
  
};

#endif	/* COBJECT_H */

