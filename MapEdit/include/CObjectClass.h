/* 
 * File:   CObjectClass.h
 * Author: Matej Pechac
 *
 * Created on September 14, 2014, 10:15 PM
 */

#ifndef COBJECTCLASS_H
#define	COBJECTCLASS_H

#include <map>
#include <string>

using namespace std;

class CObjectClass {
public:
  CObjectClass();
  CObjectClass(const CObjectClass& orig);
  virtual ~CObjectClass();
  
  int LoadFromXML(string filename);

  map<int, string>*  getClasses() { return &classes; };
  
private:
  map<int, string>  classes;
};

#endif	/* COBJECTCLASS_H */

