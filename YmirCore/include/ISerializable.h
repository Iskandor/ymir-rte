/* 
 * File:   ISerializable.h
 * Author: Matej Pechac
 *
 * Created on November 25, 2014, 8:52 PM
 */

#ifndef ISERIALIZABLE_H
#define	ISERIALIZABLE_H

#include <map>
#include <string>

using namespace std;

class ISerializable {
public:
  ISerializable() {};
  ISerializable(map<string, string>) {};
  ISerializable(const ISerializable& orig) {};
  virtual ~ISerializable() {};
  
  virtual map<string, string> exportMap() = 0;
  
  virtual void  SetID(int) = 0;
  virtual int   GetID() = 0;  
private:

};

#endif	/* ISERIALIZABLE_H */

