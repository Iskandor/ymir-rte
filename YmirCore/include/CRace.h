/* 
 * File:   CRace.h
 * Author: Matej Pechac
 *
 * Created on October 28, 2013, 1:52 PM
 */

#ifndef CRACE_H
#define	CRACE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class CRace {
public:
  CRace(string filename);
  CRace(const CRace& orig);
  virtual ~CRace();
  
  int LoadFromXML(string filename);

  vector<string> getNames();
  int            getSize();
  int            findName(string name);
  
private:
  //void importMap(map<string, string> data);
  
private:
  vector<string> names;
  
  
};

#endif	/* CRACE_H */

