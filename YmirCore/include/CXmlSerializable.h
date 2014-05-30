/* 
 * File:   CXmlSerializable.h
 * Author: Matej Pechac
 *
 * Created on March 29, 2014, 6:52 PM
 */

#ifndef CXMLSERIALIZABLE_H
#define	CXMLSERIALIZABLE_H

#include <map>
#include <string>

using namespace std;

class CXmlSerializable {
public:
  CXmlSerializable();
  CXmlSerializable(map<string, string> data);
  CXmlSerializable(const CXmlSerializable& orig);
  virtual ~CXmlSerializable();
  
  virtual map<string, string> exportMap();
private:

};

#endif	/* CXMLSERIALIZABLE_H */

