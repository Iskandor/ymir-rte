/* 
 * File:   CProjectile.h
 * Author: Matej Pechac
 *
 * Created on September 14, 2014, 11:10 PM
 */

#ifndef CPROJECTILE_H
#define	CPROJECTILE_H

#include "CObject.h"

#include <map>
#include <string>

using namespace std;

class CProjectile : public CObject {
public:
  CProjectile();
  CProjectile(map<string, string> data);
  CProjectile(const CProjectile& orig);
  virtual ~CProjectile();
  
  map<string, string> exportMap();
  
  void  SetSpeed(int value) { speed = value; };
  int   GetSpeed() { return speed; };
  
private:
  int  speed;
};

#endif	/* CPROJECTILE_H */

