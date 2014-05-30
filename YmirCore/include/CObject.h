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

using namespace std;

class CObject {
public:
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
  int   GetXSize();
  void  SetXSize(int x);
  int   GetYSize();
  void  SetYSize(int y);
  int*  GetBlockMap();
  void  SetBlockMap(int x, int y);
  void  SetBlockMap(int* block_map);  
  
protected:
  int id;
  int x_size;
  int y_size;
  int *block_map;
  
  string image_filename;
  string desc;
  
};

#endif	/* COBJECT_H */

